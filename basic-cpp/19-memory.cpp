// 内存管理 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/sg0i0lggvqgusack

#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <stack>

/*
案例一：动态数组实现
实现一个简单的动态数组类，支持添加元素、访问元素和自动扩展。
*/

class DynamicArray {
private:
    int* data_;
    int size_;
    int capacity_;
public:
    DynamicArray(int capacity = 1): data_(new int[capacity]), size_(0), capacity_(capacity) {
        if (data_ == nullptr) {
            throw std::bad_alloc();
        }
    }

    ~DynamicArray() { delete[] data_; }

    void add(int value) {
        if (size_ == capacity_) {
            resize(2 * capacity_);
        }
        data_[size_] = value;
        size_++;
    }
    
    int get(int index) const {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    void resize(int newCapacity) {
        int* newData = new int[newCapacity];
        if (newData == nullptr) {
            throw std::bad_alloc();
        }
        for (int i = 0; i < size_; i++) {
            newData[i] = data_[i];
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    int getSize() const { return size_; }
};

void ex1() {
    try {
        DynamicArray arr;
        arr.add(10);
        arr.add(20);
        arr.add(30); // 触发扩展

        std::cout << "Dynamic Array Contents:" << std::endl;
        for (size_t i = 0; i < arr.getSize(); ++i) {
            std::cout << arr.get(i) << " ";
        }
        std::cout << std::endl;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation error: " << e.what() << std::endl;
        return ;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Array access error: " << e.what() << std::endl;
        return ;
    }
}

/*
案例二：自定义内存管理器
实现一个简单的内存池，用于高效分配和释放固定大小的对象。
*/
class MemoryPool {
private:
    size_t objSize;
    size_t totalSize;
    char* pool;
    std::stack<char*> freeList;
public:
    MemoryPool(size_t objectSize, size_t poolSize)
        : objSize(objectSize), totalSize(poolSize), pool((char *)malloc(objectSize * poolSize)) {
        if (pool == nullptr) {
            throw std::bad_alloc();
        }
        for (size_t i = 0; i < poolSize; i++) {
            freeList.push(pool + i * objectSize);
        }
    }

    ~MemoryPool() { free(pool); }

    void* allocate() {
        if (freeList.empty()) {
            throw std::bad_alloc();
        }
        void* block = freeList.top();
        freeList.pop();
        return block;
    }

    void deallocate(void* block) {
        freeList.push((char *)block);
    }
};

class MyClass {
public:
    MyClass(int val) : value(val) {
        std::cout << "MyClass constructor: " << value << std::endl;
    }
    ~MyClass() {
        std::cout << "MyClass destructor: " << value << std::endl;
    }
    int value;
};

void ex2()
{
    try {
        // 创建一个能容纳 3 个 MyClass 对象的内存池
        MemoryPool pool(sizeof(MyClass), 3);

        // 分配对象内存
        void* mem1 = pool.allocate();
        void* mem2 = pool.allocate();

        // 使用“定位 new”构造对象
        MyClass* obj1 = new(mem1) MyClass(100);
        MyClass* obj2 = new(mem2) MyClass(200);

        // 使用对象
        std::cout << "obj1 value: " << obj1->value << std::endl;
        std::cout << "obj2 value: " << obj2->value << std::endl;

        // 显式调用析构函数
        obj1->~MyClass();
        obj2->~MyClass();

        // 释放内存
        pool.deallocate(mem1);
        pool.deallocate(mem2);

    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory pool allocation error: " << e.what() << std::endl;
        return ;
    }
}

/*
SimpleSharedPtr 是一个简化版的 shared_ptr 实现，旨在帮助理解其核心机制。其基本功能包括：
● 共享所有权：多个 SimpleSharedPtr 实例可以指向同一个对象，共享对该对象的所有权。
● 自动管理生命周期：当最后一个 SimpleSharedPtr 被销毁或指向其他对象时，管理的对象被自动释放。
● 引用计数：内部维护一个引用计数，记录有多少个 SimpleSharedPtr 实例指向同一个对象。
*/

struct ControlBlock {
    int ref_count;    // 引用计数

    ControlBlock() : ref_count(1){}
};

template <typename T>
class SimpleSharedPtr {
private:
    ControlBlock* ctr_block;     // 指向控制块的指针
    T* ptr;                 // 指向管理对象的指针

    // 释放资源
    void release() {
        if (ctr_block != nullptr) {
            ctr_block->ref_count--;
            std::cout << "Decremented ref_count to " << ctr_block->ref_count << std::endl;
            if (ctr_block->ref_count == 0) {
                delete ctr_block;
                delete ptr;
                std::cout << "Resource and ControlBlock destroyed." << std::endl;
            }
        }
        ctr_block = nullptr;
        ptr = nullptr;
    }

public:
    // 默认构造函数
    SimpleSharedPtr() : ctr_block(nullptr), ptr(nullptr) {}  

    // 参数化构造函数
    explicit SimpleSharedPtr(T* p) : ptr(p) {
        if (p != nullptr) {
            ctr_block = new ControlBlock();
        }
        else {
            ctr_block = nullptr;
        }
    }

    //析构函数
    ~SimpleSharedPtr() {
        release();
    }

    // 拷贝构造函数
    SimpleSharedPtr(const SimpleSharedPtr& other) : ctr_block(other.ctr_block), ptr(other.ptr) {
        if (ctr_block != nullptr) {
            ctr_block->ref_count++;
        }
    }

    // 赋值运算符
    SimpleSharedPtr& operator=(const SimpleSharedPtr& other) {
        if (this != &other) {
            release();
            ctr_block = other.ctr_block;
            ptr = other.ptr;
            if (ctr_block != nullptr) {
                ctr_block->ref_count++;
            }
        }
        return *this;
    }

    // 移动构造函数
    SimpleSharedPtr(SimpleSharedPtr&& other) : ctr_block(other.ctr_block), ptr(other.ptr) {
        other.ctr_block = nullptr;
        other.ptr = nullptr;
    }

    // 移动赋值运算符
    SimpleSharedPtr& operator=(SimpleSharedPtr&& other) {
        if (this != &other) {
            // 释放当前资源
            release();

            // 接管 `other` 的资源
            ptr = other.ptr;
            ctr_block = other.ctr_block;

            // 置 `other` 为空
            other.ptr = nullptr;
            other.ctr_block = nullptr;
        }
        return *this;
    }

    // 解引用运算符
    T& operator*() const { return *ptr; }
    // 指针运算符
    T* operator->() const { return ptr; }

    // 返回当前引用计数。
    int use_count() const { return ctr_block != nullptr ? ctr_block->ref_count : 0; }

    // 返回裸指针
    T* get() const { return ptr; }

    // 重置指针，指向新对象或 nullptr
    void reset(T* p = nullptr) {
        release();
        if (p != nullptr) {
            ctr_block = new ControlBlock();
            ptr = p;
        }
        else {
            ctr_block = nullptr;
            ptr = nullptr;
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

void ex3()
{
    std::cout << "Creating default constructed shared_ptr..." << std::endl;
    SimpleSharedPtr<Test> ptr1; // 默认构造
    std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl;

    std::cout << "\nCreating shared_ptr with resource..." << std::endl;
    SimpleSharedPtr<Test> ptr2(new Test(100)); // 非默认构造
    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;
    ptr2->show();

    std::cout << "\nCopying ptr2 to ptr3..." << std::endl;
    SimpleSharedPtr<Test> ptr3 = ptr2; // 拷贝构造
    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;
    std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl;
    ptr3->show();

    std::cout << "\nAssigning ptr3 to ptr1..." << std::endl;
    ptr1 = ptr3; // 拷贝赋值
    std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl;
    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;
    std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl;

    std::cout << "\nResetting ptr2..." << std::endl;
    ptr2.reset(new Test(200)); // 重新指向新的对象
    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;
    ptr2->show();
    std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl;
    std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl;

    std::cout << "\nExiting scope..." << std::endl;
     // ptr2, ptr1, ptr3 离开作用域

    std::cout << "End of main." << std::endl;

}

/*
std::unique_ptr 是一种独占所有权的智能指针，确保在任意时刻，只有一个 unique_ptr 实例指向特定资源。它不支持拷贝操作，只支持移动操作。
*/

template <typename T>
class SimpleUniquePtr {
private :
    T* ptr;     // 管理的对象指针
public :
    // 默认构造函数
    SimpleUniquePtr() : ptr(nullptr) {}

    // 参数化构造函数
    explicit SimpleUniquePtr(T* p) : ptr(p) {}

    //析构函数
    ~SimpleUniquePtr() {
        if (ptr != nullptr) {
            delete ptr;
        }
    }

    // 删除拷贝构造函数和赋值运算符
    SimpleUniquePtr(const SimpleUniquePtr& other) = delete;
    SimpleUniquePtr& operator=(const SimpleUniquePtr& other) = delete;

    // 移动构造函数
    SimpleUniquePtr(SimpleUniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // 移动赋值运算符
    SimpleUniquePtr& operator=(SimpleUniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // 重载解引用运算符
    T& operator*() const { return *ptr; }
    // 重载指针运算符
    T* operator->() const { return ptr; }
    // 获取裸指针
    T* get() const { return ptr; }
    // 释放所有权，返回裸指针并设为 nullptr
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    // 重置指针，指向新对象或 nullptr
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

void ex4()
{
    // 创建一个 SimpleUniquePtr
    SimpleUniquePtr<Test> ptr1(new Test(1));
    ptr1->show();
    (*ptr1).show();

    // 移动所有权到 ptr2
    SimpleUniquePtr<Test> ptr2 = std::move(ptr1);
    if (ptr1.get() == nullptr) {
        std::cout << "ptr1 is now nullptr after move." << std::endl;
    }
    ptr2->show();

    // 释放所有权
    Test* rawPtr = ptr2.release();
    if (ptr2.get() == nullptr) {
        std::cout << "ptr2 is now nullptr after release." << std::endl;
    }
    rawPtr->show();
    delete rawPtr; // 手动删除

    // 使用 reset
    ptr2.reset(new Test(2));
    ptr2->show();

    ptr2.reset(); // 自动删除
    if (ptr2.get() == nullptr) {
        std::cout << "ptr2 is now nullptr after reset." << std::endl;
    }
}


int main() {
    // ex1();
    // ex2();
    // ex3();
    ex4();
    return 0;
}