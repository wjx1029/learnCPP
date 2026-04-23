// 线程安全智能指针 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/pb5wmtntkw7autcn#rd0Gw

/*
通过将 ControlBlock::ref_count 改为 std::atomic<int>，
并在 ThreadSafeSharedPtr 中引入互斥锁来保护 ptr 和 control 的访问，
可以实现一个线程安全的智能指针。
这种实现确保了在多线程环境下，多个线程可以安全地拷贝、赋值和销毁智能指针，
同时正确管理引用计数和资源。
*/

/*
1. 引用计数的原子性：
  ○ 使用 std::atomic<int> 来保证引用计数的线程安全递增和递减。
  ○ 避免使用普通的 int，因为在多线程环境下会导致数据竞争。
2. 互斥锁的使用：
  ○ 使用 std::mutex 来保护 ptr 和 control 的访问，防止多个线程同时修改智能指针实例。
  ○ 尽量缩小锁的范围，避免在互斥锁保护的临界区内执行耗时操作，以减少性能开销。
3. 避免死锁：
  ○ 在需要同时锁定多个互斥锁时，使用 std::scoped_lock 来一次性锁定，确保锁的顺序一致，避免死锁风险。
4. 尽量遵循 RAII 原则：
  ○ 使用 std::lock_guard 或 std::scoped_lock 等 RAII 机制来管理互斥锁，确保在异常抛出时自动释放锁，防止死锁。
5. 避免多重管理：
  ○ 确保不通过裸指针绕过智能指针的引用计数管理，避免资源泄漏或重复释放。
6. 性能考虑：
  ○ 在高并发场景下，频繁的锁操作可能成为性能瓶颈。根据实际需求，可以考虑使用更轻量级的同步机制，如 std::shared_mutex（C++17）用于读多写少的场景
*/

#include <iostream>
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

// 控制块结构
struct ControlBlock {
    std::atomic<int> ref_count;

    ControlBlock() : ref_count(1) {}
};

// 线程安全的 shared_ptr 实现
template <typename T>
class ThreadSafeSharedPtr {
private:
    T* ptr;                         // 指向管理的对象
    ControlBlock* control_b;        // 指向控制块

     // 互斥锁，用于保护 ptr 和 control
    mutable std::mutex mtx;

    void release() {
        if (control_b) {
            if (--(control_b->ref_count) == 0) {
                delete ptr;
                delete control_b;
                std::cout << "Resource and ControlBlock destroyed." << std::endl;
            } else {
                std::cout << "Decremented ref_count to " << control_b->ref_count.load() << std::endl;
            }
        }
        ptr = nullptr;
        control_b = nullptr;
    }

public:

    ThreadSafeSharedPtr() : ptr(nullptr), control_b(nullptr) {
        std::cout << "Default contrusted ThreadSafeSharedPtr (nullptr)." << std::endl;
    }

    explicit ThreadSafeSharedPtr(T* p) : ptr(p) {
        if (p) {
            control_b = new ControlBlock();
            std::cout << "Constructed ThreadSafeSharedPtr, ref_count = " << control_b->ref_count.load() << std::endl;
        } else {
            control_b = nullptr;
        }
    }

    ThreadSafeSharedPtr(const ThreadSafeSharedPtr& other) {
        std::lock_guard<std::mutex> lock(other.mtx);
        ptr = other.ptr;
        control_b = other.control_b;
        if (control_b) {
            control_b->ref_count++;
            std::cout << "Copied ThreadSafeSharedPtr, ref_count = " << control_b->ref_count.load() << std::endl;
        }
    }

    ThreadSafeSharedPtr& operator=(const ThreadSafeSharedPtr& other) {
        if (other != *this) {
            // 为避免死锁，使用 std::scoped_lock 同时锁定两个互斥锁
            std::scoped_lock lock(mtx, other.mtx);
            release();
            ptr = other.ptr;
            control_b = other.control_b;
            if (control_b) {
                control_b->ref_count++;
                std::cout << "Assigned ThreadSafeSharedPtr, ref_count = " << control_b->ref_count.load() << std::endl;
            }
        }
        return *this;
    }

    ThreadSafeSharedPtr(ThreadSafeSharedPtr&& other) noexcept {
        std::lock_guard<std::mutex> lock(other.mtx);
        ptr = other.ptr;
        control_b = other.control_b;
        other.ptr = nullptr;
        other.control_b = nullptr;
        std::cout << "Moved ThreadSafeSharedPtr." << std::endl;
    }

    ThreadSafeSharedPtr& operator=(ThreadSafeSharedPtr&& other) noexcept {
        if (this != other) {
            // 为避免死锁，使用 std::scoped_lock 同时锁定两个互斥锁
            std::scoped_lock lock(mtx, other.mtx);
            release();
            ptr = other.ptr;
            control_b = other.control_b;
            other.ptr = nullptr;
            other.control_b = nullptr;
            std::cout << "Move-assigned ThreadSafeSharedPtr." << std::endl;
        }
    }

    ~ThreadSafeSharedPtr() {
        release();
    }

    T& operator*() const {
        std::lock_guard<std::mutex> lock(mtx);
        return *ptr;
    }

    T* operator->() const {
        std::lock_guard<std::mutex> lock(mtx);
        return ptr;
    }

    int use_count() const {
        std::lock_guard<std::mutex> lock(mtx);
        return control_b ? control_b->ref_count.load() : 0;
    }

    T* get() const {
        std::lock_guard<std::mutex> lock(mtx);
        return ptr;
    }

    void reset(T* p = nullptr) {
        std::lock_guard<std::mutex> lock(mtx);
        release();
        ptr = p;
        if (p) {
            control_b = new ControlBlock();
             std::cout << "Reset ThreadSafeSharedPtr, ref_count = " << control_b->ref_count.load() << std::endl;
        } else {
            control_b = nullptr;
        }
        
    }
}; 


// 测试类
class Test {
public:
    Test(int val) : value(val) {
        std::cout << "Test Constructor: " << value << std::endl;
    }
    ~Test() {
        std::cout << "Test Destructor: " << value << std::endl;
    }
    void show() const {
        std::cout << "Value: " << value << std::endl;
    }

private:
    int value;
};


void thread_func_copy(ThreadSafeSharedPtr<Test> sptr, int thread_id) {
    std::cout << "Thread " << thread_id << " is copying shared_ptr." << std::endl;
    ThreadSafeSharedPtr<Test> local_sptr = sptr;
    std::cout << "Thread " << thread_id << " copied shared_ptr, use_count = " << local_sptr.use_count() << std::endl;
    local_sptr->show();
}

void thread_func_reset(ThreadSafeSharedPtr<Test>& sptr, int new_val, int thread_id) {
    std::cout << "Thread " << thread_id << " is resetting shared_ptr." << std::endl;
    sptr.reset(new Test(new_val));
    std::cout << "Thread " << thread_id << " reset shared_ptr, use_count = " << sptr.use_count() << std::endl;
    sptr->show();
}

int main() {
    std::cout << "Creating ThreadSafeSharedPtr with Test(100)." << std::endl;
    ThreadSafeSharedPtr<Test> sptr(new Test(100));
    std::cout << "Initial use_count: " << sptr.use_count() << std::endl;

    // 创建多个线程进行拷贝操作
    const int num_threads = 5;
    std::vector<std::thread> threads_copy;

    for(int i = 0; i < num_threads; ++i) {
        threads_copy.emplace_back(thread_func_copy, sptr, i);
    }

    for(auto& t : threads_copy) {
        t.join();
    }

    std::cout << "After copy threads, use_count: " << sptr.use_count() << std::endl;

    // 创建多个线程进行 reset 操作
    std::vector<std::thread> threads_reset;

    for(int i = 0; i < num_threads; ++i) {
        threads_reset.emplace_back(thread_func_reset, std::ref(sptr), 200 + i, i);
    }

    for(auto& t : threads_reset) {
        t.join();
    }

    std::cout << "After reset threads, final use_count: " << sptr.use_count() << std::endl;

    std::cout << "Exiting main." << std::endl;
    return 0;
}