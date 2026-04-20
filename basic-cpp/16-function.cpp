// 函数用法 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/tp1g8gkiu8okf1mx

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// 内联函数
inline int square(int x) {
    return x * x;
}

// 高阶函数，接受函数指针作为参数
void execute(void (*func)()) {
    func(); // 调用传入的函数
}

// 被调用的函数
void sayHi() {
    std::cout << "Hi!" << std::endl;
}

/*
 练习1
 编写一个递归函数，计算斐波那契数列的第n项,编写一个递归函数 fibonacci，接受一个整数 n，返回斐波那契数列的第 n 项。假设 fibonacci(0) = 0，fibonacci(1) = 1
*/
int fibonacci(int n)
{
    if (n == 0 || n == 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/*
练习2
使用Lambda表达式和std::sort对一个字符串数组按长度排序
问题描述
给定一个字符串数组，使用Lambda表达式和std::sort函数对数组中的字符串按照其长度进行排序。
*/
void ex2()
{
    std::vector<std::string> fruits = {"apple", "banana", "kiwi", "strawberry", "grape", "pineapple"};

     // 使用Lambda表达式按照字符串长度进行排序
    sort(fruits.begin(), fruits.end(), [](const std::string &a, const std::string &b) -> bool {
        return a.length() < b.length();
    });

    // 输出排序后的结果
    std::cout << "Fruits sorted by length:" << std::endl;
    for(const auto &fruit : fruits)
        std::cout << fruit << " ";
    std::cout << std::endl;

}

/*
练习3
实现一个简易的事件系统，允许注册和触发回调函数
问题描述
构建一个简单的事件系统，允许用户注册多个回调函数（函数指针或Lambda表达式），并在特定事件触发时调用这些回调函数。
*/

// 定义带参数的回调函数类型
using Callback = std::function<void(int)>;

// 事件系统类
class EventSystem {
private:
    std::vector<Callback> callbacks;
public:
    // 注册回调函数
    void registerCallback(const Callback &cb)
    {
        callbacks.push_back(cb);
    }

    // 触发事件，传递参数给回调函数
    void triggerEvent(int data)
    {
        std::cout << "Event triggered with data = " << data << ". Executing callbacks..." << std::endl;
        for (auto &cb : callbacks)
        {
            cb(data);
        }
    }
};

// 示例函数作为回调
void onEvent(int data)
{
    std::cout << "Function callback recevied data: " << data << std::endl;
}

void ex3()
{
    EventSystem eventSystem;

     // 注册基于函数指针的回调
    eventSystem.registerCallback(onEvent);

    // 注册基于Lambda表达式的回调
    eventSystem.registerCallback([](int x) {
        std::cout << "Lambda callback received: " << x * 2 << std::endl;
    });

    // 注册带捕获的Lambda表达式的回调
    int multiplier = 5;
    eventSystem.registerCallback([multiplier](int x) {
        std::cout << "Lambda with capture received: " << x * multiplier << std::endl;
    });

    // 触发事件，传递参数
    eventSystem.triggerEvent(10);
}

int main()
{
    // 内联函数通过在函数前加inline关键字，建议编译器将函数代码嵌入到调用处，减少函数调用的开销。
    // 适用于函数体积小、调用频繁的函数，如访问器（getter）和修改器（setter）等。
    /*
        优点
        ● 减少函数调用的开销（如栈操作）。
        ● 可能提高程序性能。
        缺点
        ● 使得代码体积增大，可能影响缓存性能。
        ● 编译器可能忽略内联请求，特别是对于复杂函数。
    */
    {
        std::cout << "Square of 5: " << square(5) << std::endl;
    }

    // Lambda表达式 
    // [ capture_list ] ( parameter_list ) -> return_type {
    // // function body
    // }
    // 1. 捕获列表（Capture List）：指定如何访问外部变量。
    //     ○ [ ]：不捕获任何外部变量。
    //     ○ [&]：按引用捕获所有外部变量。
    //     ○ [=]：按值捕获所有外部变量。
    //     ○ [x, &y]：按值捕获x，按引用捕获y。
    // 2. 参数列表（Parameter List）：类似普通函数的参数列表，可以省略类型（C++14及以上支持自动类型推断）。
    // 3. 返回类型（Return Type）：可指定返回类型，也可省略，编译器自动推断。
    // 4. 函数体（Function Body）：Lambda的具体实现。
    {
        std::vector<int> data = {5, 2, 9, 1, 5, 6};

        // 按降序排序，使用Lambda表达式
        std::sort(data.begin(), data.end(), [](int a, int b) -> bool {
            return a > b;
        });

        std::cout << "Sorted data: ";
        for(auto num : data)
            std::cout << num << " ";
        std::cout << std::endl;
    }

    // 函数指针与回调函数
    {
        execute(sayHi);
    }

    std::cout << fibonacci(10) << std::endl;

    ex2();

    ex3();

    return 0;
}
