// 万能引用和原样转发 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/nvz9p7mway8bei8x#BAthu

#include <iostream>
#include <type_traits>


/*
模板万能引用（转发引用）

模板万能引用（也称为转发引用，英文为forwarding references）是C++11引入的一种引用类型，具有以下特点：
● 表现形式为T&&，其中T是模板参数。
● 在特定条件下，编译器会将其解析为左值引用或右值引用。
● 能够统一处理左值和右值，适用于泛型编程中的参数传递。

重要特性：
● 当模板参数T被推导为普通类型时，T&&是右值引用。
● 当模板参数T被推导为引用类型时，T&&会根据引用折叠规则解析为左值引用。

引用折叠规则
引用折叠是C++中的一项规则，用于处理引用类型的嵌套。主要规则如下：
● & &、& &&、&& & 都折叠为 &（左值引用）。
● && && 折叠为 &&（右值引用）。
*/

template<typename T>
void check_reference(T&& x){
    std::cout << std::boolalpha;
    std::cout << "T is lvalue reference: " << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "T is rvalue reference: " << std::is_rvalue_reference<T>::value << std::endl;
    std::cout << "T is rvalue : " << std::is_rvalue_reference<T&&> ::value << std::endl;
    std::cout << "x is lvalue reference: " << std::is_lvalue_reference<decltype(x)>::value << std::endl;
    std::cout << "x is rvalue reference: " << std::is_rvalue_reference<decltype(x)>::value << std::endl;
}

void demo1() {
    int a = 10;
    check_reference(a);          // T被推导为 int&， 因此 T&& -> int& && -> int&
    check_reference(20);         // T被推导为 int，  T&& -> int&&

    int &&c = 100;
    check_reference(c);                 // T被推导为 int&， 因此 T&& -> int& && -> int&
    check_reference(std::move(c));      // T被推导为 int， 因此 T&& -> int&&
}

// 目标函数，分别有左值和右值的重载
void process(int&x){
    std::cout << "process(int&)" << std::endl;
}

void process(int&& x){
    std::cout << "process(int&&)" << std::endl;
}

// 通用的包装函数，使用转发引用
template<typename T>
void wrapper(T&& arg) {
    process(std::forward<T>(arg)); // 原样转发
}

void demo2() {
    int a = 10;
    wrapper(a);          // 传递左值，调用process(int&)
    wrapper(20);         // 传递右值，调用process(int&&)
}

/*
原样转发（Perfect Forwarding）

原样转发（Perfect Forwarding）是指在模板函数中，将接收到的参数以其原有的值类别（左值或右值）传递给另一个函数。这项技术确保了泛型代码能够像手写特定代码那样高效和正确地处理参数。

作用：
● 保持参数的值类别，确保正确调用函数重载。
● 利用移动语义，避免不必要的拷贝，提升性能。
● 编写通用、复用性强的代码。

实现原理:
原样转发通常结合模板万能引用（转发引用）和std::forward来实现。具体流程如下：
1. 使用模板万能引用（T&&）接收参数。
2. 使用 std::forward<T>(arg) 将参数转发给目标函数。
  ○ std::forward根据T的类型，将参数转换为左值或右值。
  ○ 如果参数原本是左值，std::forward返回左值引用。
  ○ 如果参数原本是右值，std::forward返回右值引用。

在泛型编程中，函数模板可能需要将接收到的参数传递给其他函数。若不使用原样转发，参数会失去原有的值类别信息，可能导致以下问题：
● 右值参数被当作左值处理，无法利用移动语义，导致性能下降。
● 无法正确调用目标函数的重载版本。
● 增加不必要的拷贝开销，影响程序性能。
通过原样转发，可以确保参数在传递过程中保持其原有的左值或右值特性，提升代码的效率和灵活性。
*/

// 类的定义
class Person {
public:
    std::string name;
    int age;

    // 左值引用构造函数
    Person(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Constructed Person(const std::string&, int)" << std::endl;
    }

    // 右值引用构造函数
    Person(std::string&& n, int a) : name(std::move(n)), age(a) {
        std::cout << "Constructed Person(std::string&&, int)" << std::endl;
    }
};

// 工厂函数，使用原样转发构造函数参数
template<typename T, typename... Args>
T create(Args&&... args) {
    return T(std::forward<Args>(args)...);
}

void demo3() {
    std::string name = "Alice";

    // 传递左值
    Person p1 = create<Person>(name, 30); 
    // 传递右值
    Person p2 = create<Person>(std::string("Bob"), 25);    
}

// 类的定义
class BigObject {
public:
    std::string data;

    BigObject(const std::string& d) : data(d) {
        std::cout << "BigObject constructed with lvalue" << std::endl;
    }

    BigObject(std::string&& d) : data(std::move(d)) {
        std::cout << "BigObject constructed with rvalue" << std::endl;
    }
};

// 处理函数，左值和右值的重载
void process(const BigObject& obj) {
    std::cout << "Processing lvalue BigObject" << std::endl;
}

void process(BigObject&& obj) {
    std::cout << "Processing rvalue BigObject" << std::endl;
}

// 包装函数，不使用原样转发
template<typename T>
void bad_wrapper(T&& obj) {
    process(obj); // 始终以左值形式传递
}

// 包装函数，使用原样转发
template<typename T>
void good_wrapper(T&& obj) {
    process(std::forward<T>(obj)); // 原样转发
}

void demo4() {
    std::string s = "Sample data";

    // 使用bad_wrapper
    BigObject bo1 = BigObject(s);              // 使用lvalue构造
    BigObject bo2 = BigObject(std::move(s));   // 使用rvalue构造

    bad_wrapper(bo1); // 始终作为左值处理
    bad_wrapper(BigObject("Temp")); // 作为左值处理，浪费移动语义

    // 使用good_wrapper
    good_wrapper(bo1); // 作为左值处理
    good_wrapper(BigObject("Temp")); // 作为右值处理，利用移动语义    
}

int main() {
    // demo1();
    // demo2();
    // demo3();
    demo4();

    return 0;
}