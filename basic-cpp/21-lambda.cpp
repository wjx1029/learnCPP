// lambda和function : https://www.yuque.com/lianlianfengchen-cvvh2/zack/ls29zgpknsocqpq9

#include <iostream>
#include <functional>
#include <vector>
// #include <algorithm>

/*
● 简单回调： 使用函数指针或Lambda表达式。
● 需要携带状态或更复杂逻辑： 使用Lambda表达式或仿函数（Functors）。
● 接口要求 std::function： 使用 std::function，不过要注意可能的性能开销。
● 参数预绑定： 使用 std::bind，但在现代C++中，许多情况下Lambda表达式能达到相同效果且更直观。
*/


// 可调用对象	                            描述	                                        示例用法

// 函数指针	                 指向普通函数或静态成员函数的指针	                        int (*func)(int) = &funcName;
// 仿函数（Functors）	     重载了 operator() 的类实例，可以携带状态	                struct Foo { void operator()(); };
// Lambda表达式	            定义在表达式中的匿名函数，支持捕获上下文变量	              [capture](params) { /* code */ }
// std::function	       通用的可调用对象包装器，能够封装任何符合签名的可调用对象	       std::function<void(int)> func;
// std::bind	           绑定函数或可调用对象的部分参数，生成新的可调用对象	          auto newFunc = std::bind(func, _1);



// 1.普通函数
int add(int a, int b) {
    return a + b;
}

// 2.仿函数
struct Multiply {
    int operator()(int a, int b) const {
        return a * b;
    }
};

// 3.Lambda表达式
auto subtract = [](int a, int b) -> int {
    return a - b;
};

// 4.类定义
class Calculator {
public:
    int subtract(int a, int b) const {
        return a - b;
    }

    void displayOperation(const std::string& op, int result) const {
        std::cout << op << "结果: " << result << std::endl;
    }
};

// 5.静态成员函数
class Logger {
public:
    static void log(const std::string& message) {
        std::cout << "Log: " << message << std::endl;
    }
};

int main() {
    // 1.函数指针
    int (*ptr_func)(int,int) = &add;
    std::cout << "Add (Function Pointer): " << ptr_func(10, 5) << std::endl; // 输出: 15
    auto pf = &add;
    std::cout << "Add (Function Pointer): " << pf(10, 5) << std::endl; // 输出: 15

    // 2.仿函数
    Multiply multiply;
    std::cout << "Multiply (Functors): " << multiply(10, 5) << std::endl; // 输出: 50

    // 3.Lambda表达式
    std::cout << "Subtract (Lambda): " << subtract(10, 5) << std::endl; // 输出: 50

    // 4.std::function 封装不同的可调用对象
    std::function<int(int, int)> funcAdd = add;
    std::function<int(int, int)> funcMultiply = multiply;
    std::function<int(int, int)> funcSubtract = subtract;

    std::cout << "Add (std::function): " << funcAdd(20, 10) << std::endl; // 输出: 30
    std::cout << "Subtract (std::function): " << funcSubtract(20, 4) << std::endl; // 输出: 16
    std::cout << "Multiply (std::function): " << funcMultiply(4, 5) << std::endl; // 输出: 20

    // 5.std::bind 绑定部分参数
    auto add5 = std::bind(add, 5, std::placeholders::_1);
    std::cout << "5 + 10 = " << add5(10) << std::endl; // 输出: 15

    auto multiplyBy2 = std::bind(multiply, 2, std::placeholders::_1);
    std::cout << "2 * 10 = " << multiplyBy2(10) << std::endl; // 输出: 20

    // 6.std::bind 绑定类成员函数
    Calculator calc;

    // 使用 std::bind 绑定成员函数 subtract
    auto boundSubtract = std::bind(&Calculator::subtract, &calc, 15, 5);
    std::cout << "15 - 5 = " << boundSubtract() << std::endl; // 输出: 10

    // 使用 std::bind 绑定成员函数 displayOperation
    auto displayAdd = std::bind(&Calculator::displayOperation, &calc, "Add", std::placeholders::_1);
    auto displayResult = funcAdd;
    int addResult = displayResult(7, 8);
    displayAdd(addResult);

    // 7.绑定静态成员函数
    auto logFunc = std::bind(&Logger::log, std::placeholders::_1);
    logFunc("This is a static log message.");

    // 8.使用 std::function 存储混合可调用对象
    std::vector<std::function<void()>> operations;

    operations.emplace_back([&]() { std::cout << "Lambda Operation" << std::endl; });
    operations.emplace_back(std::bind(&Calculator::displayOperation, &calc, "Multiply", 30));
    operations.emplace_back([&]() { std::cout << "Add5(10): " << add5(10) << std::endl; });
    operations.emplace_back([&]() { Logger::log("Lambda-based log message."); });

    // 执行所有操作
    for (auto& op : operations)
    {
        op();
    }

    return 0;

}

/*
1. 函数指针: 定义并使用了指向 add 函数的函数指针 funcPtr。
2. 仿函数（Functors）: 定义了 Multiply 结构体，并使用其实例 multiply 进行乘法运算。
3. Lambda表达式: 定义了一个用于减法的Lambda subtract。
4. std::function: 封装了不同类型的可调用对象，包括普通函数、Lambda和仿函数。
5. std::bind: 绑定 add 和 multiply 函数的部分参数，生成新的可调用对象 add5 和 multiplyBy2。
6. 绑定类成员函数: 使用 std::bind 绑定 Calculator 类的成员函数 subtract 和 displayOperation。
7. 绑定静态成员函数: 使用 std::bind 绑定 Logger 类的静态成员函数 log。
8. 混合可调用对象容器: 使用 std::function 和 std::vector 存储并执行不同类型的可调用对象，包括Lambda、绑定成员函数和静态成员函数。
*/