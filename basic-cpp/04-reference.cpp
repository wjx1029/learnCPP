// 引用类型 ：https://www.yuque.com/lianlianfengchen-cvvh2/zack/szxat479iccyllqc

#include <iostream>

std::string foo() {
    return std::string("Hello, World!"); // 返回的临时字符串是一个右值
}

int main()
{
    // 定义变量a
    int a = 100;
    // 定义引用b并且指向a, b就是a的别名
    int &b = a;
    std::cout << "a的地址为:" << &a << std::endl;
    std::cout << "b的地址为:" << &b << std::endl;

    // 输出a和b的值
    std::cout << "a的值:" << a << std::endl;
    std::cout << "b的值: " << b << std::endl;

    // a和b是指向同一个变量。所以我们修改a的值，b的值也会变
    a = 200;
    std::cout << "修改a的值后，a和b的值分别为:\n"
              << a << std::endl;
    std::cout << b << std::endl;

    // 修改b的值，a的值也会变
    b = 300;
    std::cout << "修改b的值后，a和b的值分别为:\n" << a << std::endl;
    std::cout << b << std::endl;

    /*
    1. 必须初始化：引用在创建时必须被初始化，它必须指向某个已存在的对象。
    2. 一旦绑定，不可改变：引用一旦被初始化后，它将一直保持与其初始对象的绑定，不能改变为另一个对象的引用。
    3. 没有空引用：引用必须指向某个对象，不能存在空引用。
    4. 引用可以是const的，这表示你不能通过引用来修改它所指向的对象的值。
    */

    const int &c = a;
    // c = 500;

    /* 左值引用和右值引用
    在C++中，左值（lvalue）和右值（rvalue）是表达式的两种基本分类，
    它们决定了表达式的结果在内存中的位置和状态。
    左值通常指的是具有持久状态的对象，它们有明确的内存地址，可以被多次赋值。
    而右值通常是临时的、没有持久状态的值，它们通常没有内存地址，或者其内存地址在表达式结束后就变得无效。
    
    C++11引入了右值引用（rvalue reference），用T&&表示，
    作为对左值引用（lvalue reference，用T&表示）的补充。
    这一特性极大地增强了C++的表达能力，特别是在资源管理和性能方面。
    */ 

    int&& d = 20; // c是整数字面量20的右值引用（但这种情况不常见，通常用于函数参数或返回值）

    std::string &&e = foo(); // d是foo()返回的临时字符串的右值引用

    std::cout << e << std::endl;

}