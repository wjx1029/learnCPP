// 手写双端队列 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/qsh5rbe88agaugpm#l1Vh9

/*
实现了一个支持双端插入和删除的双端队列（deque），并添加了迭代器支持，使其能够与标准的 C++ 迭代器接口兼容。这个实现包含了以下关键点：
1. 内部缓冲区管理：
  ○ 使用动态数组并采用环形缓冲区的方式，支持高效的双端操作。
  ○ 自动调整缓冲区的容量，确保在元素数量增加时仍能保持高效。
2. 迭代器实现：
  ○ 定义了一个嵌套的 Iterator 类，支持前向和后向遍历。
  ○ 重载了必要的运算符（如 *, ->, ++, --, ==, !=），以实现与标准迭代器的兼容。
3. 基本操作：
  ○ push_front 和 push_back：分别在队列的前端和后端插入元素。
  ○ pop_front 和 pop_back：分别从队列的前端和后端删除元素。
  ○ front 和 back：访问队列的前端和后端元素。
*/

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <iterator>

template <typename T>
class Deque {
private:
    T* buffer;               // 内部缓冲区
    size_t capacity;         // 缓冲区容量
    size_t front_idx;        // 头部索引
    size_t back_idx;         // 尾部索引
    size_t count;            // 当前元素数量 

    // 调整容量
    void resize(size_t newSize) {
        T* newBuffer = new T[newSize];
        for (size_t i = 0; i < count; i++) {
            newBuffer[i] = buffer[(front_idx + i) % capacity];
        }
        delete [] buffer;
        buffer = newBuffer;
        front_idx = 0;
        back_idx = count;
    }

public:
    // 构造函数
    Deque(size_t init_capacity = 8) {
        buffer = new T[init_capacity];
        capacity = init_capacity;
        front_idx = 0;
        back_idx = 0;
        count = 0;
    }

    // 析构函数
    ~Deque() {
        delete [] buffer;
    }

    // 复制构造函数
    Deque(const Deque& other) {
        buffer = new T[other.capacity];
        capacity = other.capacity;
        front_idx = other.front_idx;
        back_idx = other.back_idx;
        count = other.count;
        for (size_t i = 0; i < count; i++) {
            buffer[(front_idx + i) % capacity] = other.buffer[(other.front_idx + i) % other.capacity];
        }
    }

    // 赋值运算符
    Deque& operator=(const Deque& other) {
        if (this != &other) {
            delete [] buffer;
            resize(other.capacity);
            capacity = other.capacity;
            front_idx = other.front_idx;
            back_idx = other.back_idx;
            count = other.count;
            for (size_t i = 0; i < count; i++) {
                buffer[(front_idx + i) % capacity] = other.buffer[(other.front_idx + i) % other.capacity];
            }
        }
        return *this;
    }

    // 检查是否为空
    bool empty() {
        return count == 0;
    }

    // 获取当前元素数量
    size_t size() {
        return count;
    }

    // 从头部插入元素
    void push_front(const T& val) {
        if (size() == capacity) {
            resize(capacity * 2);
        }
        front_idx = front_idx == 0 ? capacity - 1 : front_idx - 1;
        buffer[front_idx] = val;
        count++;
    }

    // 从尾部插入元素
    void push_back(const T& val) {
        if (size() == capacity) {
            resize(capacity * 2);
        }
        buffer[back_idx] = val;
        back_idx = (back_idx + 1) % capacity;
        count++;
    }

    // 从头部弹出元素
    void pop_front() {
        if (empty()) {
            throw std::out_of_range("Deque is empty.");
        }
        count--;
        front_idx = (front_idx + 1) % capacity;
    }

    // 从尾部弹出元素
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Deque is empty.");
        }
        count--;
        back_idx = back_idx == 0 ? capacity - 1 : back_idx - 1;
    }

    // 获取头部元素
    T& front() {
        if (empty()) {
            throw std::out_of_range("Deque is empty.");
        }
        return buffer[front_idx];
    }

    // 获取头部元素（常量引用）
    const T& front() const {
        if (empty()) {
            throw std::out_of_range("Deque is empty.");
        }
        return buffer[front_idx];
    }

    // 获取尾部元素 
    T& back() {
        if (empty()) {
            throw std::out_of_range("Deque is empty.");
        }
        return back_idx == 0 ? buffer[capacity - 1] : buffer[back_idx - 1];        
    }

    // 获取尾部元素（常量引用）
    const T& back() const {
        if (empty()) {
            throw std::out_of_range("Deque is empty.");
        }
        return back_idx == 0 ? buffer[capacity - 1] : buffer[back_idx - 1];        
    }

    // 迭代器类的定义
    class Iterator {
    private:
        Deque<T>* deque_ptr;
        size_t index;
        size_t pos;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        
        Iterator(Deque<T>* deque, size_t position) : deque_ptr(deque), pos(position) {}

        // 解引用操作
        reference operator*() const {
            size_t real_idx = (deque_ptr->front_idx + pos) % deque_ptr->capacity;
            return deque_ptr->buffer[real_idx];
        }

        // 指针操作
        pointer operator->() const {
            size_t real_idx = (deque_ptr->front_idx + pos) % deque_ptr->capacity;
            return &(deque_ptr->buffer[real_idx]);
        }

        // 前缀操作符 ++i
        Iterator& operator++() {
            ++pos;
            return *this;
        }

        // 后缀操作符 ++i
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++pos;
            return tmp;
        }

        // 前缀操作符 --i
        Iterator& operator--() {
            --pos;
            return *this;
        }

        // 后缀操作符 --i
        Iterator operator--(int) {
            Iterator tmp = *this;
            --pos;
            return tmp;
        }

        // 等价操作符 ==
        bool operator==(const Iterator& other) const {
            return (deque_ptr == other.deque_ptr) && (pos == other.pos);
        }

        // 不等价操作符 !=
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    // 获取头部迭代器
    Iterator begin() {
        return Iterator(this, 0);
    }

    // 获取尾部迭代器
    Iterator end() {
        return Iterator(this, count);
    }

};


// 测试
int main() {
    Deque<std::string> dq;

    // 在后面插入元素
    dq.push_back("Apple");
    dq.push_back("Banana");
    dq.push_back("Cherry");

    // 在前面插入元素
    dq.push_front("Date");
    dq.push_front("Elderberry");

    // 显示队列大小
    std::cout << "Deque 大小: " << dq.size() << std::endl;

    // 使用迭代器进行遍历
    std::cout << "Deque 元素: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试复制构造函数
    Deque<std::string> dq2 = dq;

    // 验证复制构造函数是否成功
    std::cout << "复制构造函数测试: ";
    for (auto it = dq2.begin(); it != dq2.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试赋值运算符
    Deque<std::string> dq3 = dq;

    // 验证赋值运算符是否成功
    std::cout << "赋值运算符测试: ";
    for (auto it = dq3.begin(); it != dq3.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 访问前端和后端元素
    std::cout << "前端元素: " << dq.front() << std::endl;
    std::cout << "后端元素: " << dq.back() << std::endl;

    // 删除元素
    dq.pop_front();
    dq.pop_back();

    // 再次遍历
    std::cout << "删除元素后的 Deque: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}