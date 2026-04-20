// 类的基础 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/dt8bgukh8gc7rhlr#YLaTX



#include <iostream>
#include <cstring>
#include <ostream>

// ● 默认构造函数：没有参数的构造函数。
// ● 参数化构造函数：接受参数以初始化对象。
// ● 拷贝构造函数：用一个对象初始化另一个对象。
// ● 移动构造函数（C++11）：从临时对象“移动”资源。
class Example {
public:
    // 默认构造函数
    Example() : data_(0) {
        std::cout << "Default constructor called.\n";
    }

    // 参数化构造函数
    Example(int data) : data_(data) {
        std::cout << "Parameterized constructor called with data = " << data_ << ".\n";
    }

    // 拷贝构造函数
    Example(const Example& other) : data_(other.data_) {
        std::cout << "Copy constructor called.\n";
    }

    // 移动构造函数
    Example(Example&& other) noexcept : data_(other.data_) {
        other.data_ = 0;
        std::cout << "Move constructor called.\n";
    }

    // 析构函数
    ~Example() {
        std::cout << "Destructor called for data = " << data_ << ".\n";
    }

private:
    int data_;
};

// ● 移动语义（Move Semantics）：允许资源的所有权从一个对象转移到另一个对象，避免不必要的拷贝，提高性能。

// 移动构造函数与移动赋值运算符
// ● 移动构造函数：ClassName(ClassName&& other) noexcept;
// ● 移动赋值运算符：ClassName& operator=(ClassName&& other) noexcept;
class MoveExample {
public:
    // 构造函数
    MoveExample(int size) : size_(size), data_(new int[size]) {
        std::cout << "Constructor called.\n";
    }

    // 拷贝构造函数
    MoveExample(const MoveExample& other) : size_(other.size_), data_(new int[other.size_]) {
        std::copy(other.data_, other.data_ + size_, data_);
        std::cout << "Copy constructor called.\n";
    }

    // 移动构造函数
    MoveExample(MoveExample&& other) noexcept : size_(other.size_), data_(other.data_) {
        other.size_ = 0;
        other.data_ = nullptr;
        std::cout << "Move constructor called.\n";
    }

    // 拷贝赋值运算符
    MoveExample& operator=(const MoveExample& other) {
        std::cout << "Copy assignment operator called.\n";
        if (this == &other)
            return *this;

        delete[] data_;
        size_ = other.size_;
        data_ = new int[size_];
        std::copy(other.data_, other.data_ + size_, data_);
                return *this;
    }

    // 移动赋值运算符
    MoveExample& operator=(MoveExample&& other) noexcept {
        std::cout << "Move assignment operator called.\n";
        if (this == &other)
            return *this;

        delete[] data_;
        size_ = other.size_;
        data_ = other.data_;

        other.size_ = 0;
        other.data_ = nullptr;
        return *this;
    }

    // 析构函数
    ~MoveExample() {
        delete[] data_;
        std::cout << "Destructor called.\n";
    }

private:
    int size_;
    int* data_;
};


void demo() {
    {
        Example ex1;               // 调用默认构造函数
        Example ex2(42);           // 调用参数化构造函数
        Example ex3 = ex2;         // 调用拷贝构造函数
        Example ex4 = std::move(ex2); // 调用移动构造函数
    }

    {
        MoveExample ex1(100);                 // Constructor
        MoveExample ex2 = ex1;                // Copy Constructor
        MoveExample ex3 = MoveExample(200);   // Move Constructor

        MoveExample ex4(300);
        ex4 = ex1;                             // Copy Assignment
        ex4 = MoveExample(400);                // Move Assignment       
    }
    
}

/*
项目：实现自定义MyString类
目标：创建一个简单的MyString类，支持拷贝构造，默认构造，有参构造，支持输出和比较等。
*/
class MyString {
private:
    char* data_;     // 动态分配的字符数组

public:
    // 默认构造
    MyString() : data_(nullptr) {}

    // 参数构造
    MyString(const char *str)
    {
        if (str == nullptr) {
            data_ = nullptr;
        }
        else {
            data_ = new char[strlen(str) + 1];
            strcpy(data_, str);
        }
    }

    // 拷贝构造
    MyString(const MyString &other) 
    {
        if (other.data_) {
            data_ = new char[strlen(other.data_) + 1];
            strcpy(data_, other.data_);
        } else {
            data_ = nullptr;
        }
    }

    // 赋值运算符重载
    MyString& operator=(const MyString &other)
    {
        if (this == &other) return *this;

        delete[] data_;     // 释放原有内存
        if (other.data_) {
            data_ = new char[strlen(other.data_) + 1];
            strcpy(data_, other.data_);
        } else {
            data_ = nullptr;
        }
        return *this;
    }

    // 移动构造
    MyString(MyString &&other) noexcept
    {
        if (other.data_) {
            data_ = new char[strlen(other.data_) + 1];
            strcpy(data_, other.data_);
            other.data_ = nullptr;
        } else {
            data_ = nullptr;
        }
    }

    // 友元函数重载<<
    friend std::ostream& operator<<(std::ostream& os, const MyString &mystring);

    // 重载比较运算符
    bool operator==(const MyString& other)
    {
        if (data_ == nullptr && other.data_ == nullptr) return true;
        if (data_ == nullptr || other.data_ == nullptr) return false;
        return strcmp(data_, other.data_) == 0;
    }

    // 析构函数
    ~MyString()
    {
        delete[] data_;
    }
};

std::ostream& operator<<(std::ostream& os, const MyString &mystring)
{
    os << mystring.data_;
    return os;
}

void ex()
{
    MyString s1;    // 默认构造
    MyString s2("hello world");     // 参数构造
    MyString s3 = s2;              // 拷贝构造
    MyString s4;
    s4 = s2;                      // 赋值运算符
    // MyString s5 = MyString("I love you"); // 移动构造
    MyString s5 = std::move(MyString("hello")); // 移动构造
    std::cout << s2 << std::endl;
    std::cout << s5 << std::endl;
    std::cout << (s2 == s3) << std::endl;
    std::cout << (s2 == s4) << std::endl;
    std::cout << (s2 == s5) << std::endl;
}

int main()
{
    demo();
    ex();
    return 0;
}