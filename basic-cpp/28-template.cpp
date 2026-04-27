// 模板 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/xm79tzu27moll8r9#dIWut

/*
C++ 模板机制是实现泛型编程的核心工具，通过类型参数化和编译期计算，极大地提升了代码的复用性、灵活性和性能。
从基础的函数模板和类模板，到高级的模板特化、变参模板、模板元编程、SFINAE 和 Concepts，掌握模板的各个方面能够帮助开发者编写更高效、更加通用的 C++ 代码。
在实际应用中，合理运用模板不仅可以简化代码结构，还可以提高代码的可维护性和可扩展性。
然而，模板的复杂性也要求开发者具备扎实的 C++ 基础和良好的编程习惯，以避免过度复杂化和难以调试的问题。
*/

/*
综合案例：结合模板特化与折叠表达式
为了进一步巩固对模板特化和折叠表达式的理解，本节将通过一个综合案例展示如何将两者结合使用。
案例描述
实现一个通用的日志记录器Logger，能够处理任意数量和类型的参数，并根据不同的类型组合调整输出格式。具体需求包括：
1. 对于普通类型，使用通用的打印格式。
2. 对于指针类型，打印指针地址或指向的值。
3. 对于std::string类型，使用专门的格式。
4. 支持可变数量的参数，通过折叠表达式实现参数的逐一打印。
实现步骤
1. 定义通用类模板Logger，使用模板特化和偏特化处理不同类型。
2. 实现log函数，使用模板折叠表达式逐一打印参数。
*/

#include <iostream>
#include <string>
#include <type_traits>

// 通用类模板
template <typename T, typename Enable = void>
class Logger {
public:
    static void log(const T& value) {
        std::cout << "General Logger: " << value << std::endl;
    }
};

// 类模板偏特化：当 T 是指针类型时
template <typename T>
class Logger<T, typename std::enable_if<std::is_pointer<T>::value>::type> {
public:
    static void log(const T value) {
        if (value) {
            std::cout << "Pointer Logger: " << *value << std::endl;
        } else {
            std::cout << "Pointer Logger: nullptr" << std::endl;
        }
        
    }
};

// 类模板全特化：当 T 是 std::string 类型时
template <>
class Logger<std::string> {
public:
    static void log(const std::string& value) {
        std::cout << "String Logger: " << value << std::endl;
    }
};

// 函数模板，用于递归调用 Logger::log
template <typename T>
void logOne(const T& value) {
    Logger<T>::log(value);
}

// 使用模板折叠表达式实现多参数日志记录
template <typename... Args>
void logAll(const Args&... args) {
    (logOne(args), ...);
}


int main() {
    int a = 10;
    double b = 3.14;
    std::string s = "Hello, World!";
    int* ptr = &a;
    double* pNull = nullptr;

    // 使用 Logger 类模板进行特化打印
    Logger<int>::log(a);          // 输出：General Logger: 10
    Logger<double*>::log(pNull);  // 输出：Pointer Logger: nullptr
    Logger<std::string>::log(s);  // 输出：String Logger: "Hello, World!"

    std::cout << "\nLogging multiple parameters:" << std::endl;
    logAll(a, b, s, ptr, pNull);
    /*
    输出：
    General Logger: 10
    General Logger: 3.14
    String Logger: "Hello, World!"
    Pointer Logger: 10
    Pointer Logger: nullptr
    */

    return 0;
}

/*
最佳实践与注意事项
掌握模板的最佳实践有助于编写高效、可维护的代码，同时避免常见的陷阱和问题。
模板定义与实现分离
对于类模板，通常将模板的声明和定义放在同一头文件中，以确保编译器在实例化模板时能够看到完整的定义。尽管可以尝试将模板定义分离到源文件，但需要结合显式实例化，这会增加复杂性，且不适用于广泛使用的模板。
推荐做法：
● 类模板：将声明和实现统一在头文件中。
● 函数模板：同样将声明和实现统一在头文件中，或使用显式实例化。
避免过度模板化
虽然模板提供了极大的灵活性，但过度复杂的模板会导致代码难以理解、维护和编译时间增加。
建议：
● 只在必要时使用模板。
● 保持模板的简单性和可读性，避免过度嵌套和复杂的特化。
● 合理使用类型特性和 Concepts 进行约束。
提高编译速度的方法
模板的广泛使用可能导致编译时间显著增加。以下方法有助于优化编译速度：
1. 预编译头文件（Precompiled Headers）：将频繁使用的模板库放入预编译头中，加速编译。
2. 显式实例化：通过显式实例化减少模板的重复编译。
3. 模块化编程（C++20 Modules）：利用模块化将模板库进行编译和链接，减少编译时间。
4. 合理分割头文件：避免头文件中的模板定义过大，分割成较小的模块。
代码复用与库设计
模板是实现高度复用库组件的有效手段，如标准库（std::vector、std::map 等）广泛使用模板。设计模板库时，需考虑以下因素：
● 接口的一致性：保持模板库的接口简洁、一致，便于使用者理解和使用。
● 文档与示例：提供详细的文档和示例代码，帮助使用者理解模板库的用法。
● 错误信息友好：通过 Concepts、SFINAE 等机制提供清晰的错误信息，降低使用门槛。
● 性能优化：利用模板的编译期计算和内联等特性，提高库组件的性能。
避免模板错误的困惑
模板错误通常复杂且难以理解，以下方法有助于减少模板错误的困惑：
● 逐步调试：从简单的模板开始，逐步增加复杂性，便于定位错误。
● 使用编译器警告与工具：开启编译器的警告选项，使用静态分析工具检测模板代码中的问题。
● 代码注释与文档：详细注释复杂的模板代码，提供文档说明其设计和用途。

总结
C++ 模板机制是实现泛型编程的核心工具，通过类型参数化和编译期计算，极大地提升了代码的复用性、灵活性和性能。从基础的函数模板和类模板，到高级的模板特化、变参模板、模板元编程、SFINAE 和 Concepts，掌握模板的各个方面能够帮助开发者编写更高效、更加通用的 C++ 代码。
在实际应用中，合理运用模板不仅可以简化代码结构，还可以提高代码的可维护性和可扩展性。然而，模板的复杂性也要求开发者具备扎实的 C++ 基础和良好的编程习惯，以避免过度复杂化和难以调试的问题。
通过本教案的系统学习，相信您已经具备了全面理解和运用 C++ 模板的能力，能够在实际项目中高效地利用模板特性，编写出更为优秀的代码。
*/