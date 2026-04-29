# C++ 学习笔记

本笔记基于 learnCPP 仓库 basic-cpp 目录的学习，系统梳理了从变量基础到模板、智能指针、线程安全等核心知识点。每个小节对应一个 .cpp 文件。

## 01-variable.cpp
变量定义、基本类型和输出，演示 boolalpha。

## 02-scope.cpp
作用域、存储类别（auto、register、static、extern、mutable）、全局变量和局部静态变量。

## 03-include_extern.cpp
头文件(.h)与源文件(.cpp)的分离，使用 #include 和防卫宏。

## 04-reference.cpp
引用类型：别名，必须初始化，不能为空，常用于函数参数返回值。

## 05-pointer.cpp
指针：存储地址，解引用，空指针，指针运算，数组与指针关系。

## 06-const.cpp
const 用法：修饰变量、指针（指针常量、常量指针）、成员函数、函数参数返回值。

## 07-auto-decltype.cpp
auto 类型推导，decltype 推导表达式类型，typedef 与 using 别名。

## 08-student-info-system.cpp
结构体 struct：定义、成员访问，示例学生信息管理系统。

## 09-email-confirm-tool.cpp
示例项目：用户输入验证工具，验证邮箱格式（含 @ 和 .）。

## 09-simple-text-analyzer.cpp
示例项目：简易文本分析器，统计单词数、频率、最长单词等。

## 09-string.cpp
std::string 用法：构造、连接、访问、子串、查找、替换、比较。

## 10-inventory-manage-system.cpp
示例项目：动态库存管理系统，增删改查商品信息。

## 10-vector.cpp
std::vector 容器：动态数组，增删（push_back, pop_back, insert, erase），遍历，迭代器失效。

## 11-iterator.cpp
迭代器概念：begin(), end(), 运算符重载，不同容器的迭代器类型。

## 12-array.cpp
内置数组和 std::array：固定大小，栈分配，遍历，多维数组退化为指针。

## 13-multiarray.cpp
多维数组：声明、初始化，行主序，指针地址连续。

## 14-operator.cpp
运算符重载基础：成员函数 vs 非成员函数，友元函数，输入输出流重载。

## 15-try-throw-catch.cpp
异常处理：throw, try-catch，异常匹配，异常规范，std::exception。

## 16-function.cpp
函数：默认参数，内联函数，递归，函数重载，函数指针。

## 17-basic-class.cpp
类基础：成员变量、成员函数，构造函数、析构函数，this 指针，静态成员。

## 18-advanced-class.cpp
继承与多态：公有、保护、私有继承，虚函数，纯虚函数，抽象类，虚析构。

## 19-memory.cpp
内存管理：new/delete，new[]/delete[]，内存泄漏，野指针，内存越界。

## 20-smart-pointer.cpp
智能指针：std::unique_ptr, std::shared_ptr, std::weak_ptr，所有权，循环引用。

## 21-lambda.cpp
lambda 表达式：捕获列表([]), 参数列表, 可变(mutable), 异常说明, 返回类型，std::function。

## 22-delist.cpp
STL 列表 std::list：双向链表，增删 O(1)，不支持随机访问。

## 23-dequeue.cpp
手写双端队列：环形缓冲实现，支持两端进出 O(1)。

## 24-thread-safe-shared-pointer.cpp
线程安全智能指针：在多线程环境下使用 std::shared_ptr 需要额外同步，或使用 atomic_shared_ptr。

## 25-map.cpp
std::map：红黑树实现，有序键值对，查找/插入/删除 O(log n)。

## 26-unorderedmap.cpp
std::unordered_map：哈希表实现，无序，平均 O(1)，最坏 O(n)。

## 27-operator-overloading.cpp
运算符重载实战：算术运算符，比较运算符，赋值运算符，下标运算符，函数调用运算符。

## 28-template.cpp
函数模板和类模板：模板参数，具体化，偏特化，模板实参推断。

## 29-template-exercise.cpp
模板练习题：编写通用的交换函数，最大值查找，简单容器。

## 30-forwarding-reference-perfect-forwarding.cpp
万能引用（T&&）和 std::forward 原样转发，解决完美转发问题。

## 31-single-instance.cpp
单例模式演变：饿汉式，懒汉式（线程不安全），双重检查锁定，std::call_once，Meyers 单例。

## 32-stream.cpp
常用流：std::cin, std::cout, std::cerr, 文件流 std::ifstream/ofstream，字符串流 std::stringstream，格式控制。
