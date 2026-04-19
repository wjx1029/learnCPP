// 异常处理 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/cfxskkc7bmf0zvtu#FloKT

/*
try, catch, 和 throw 语句
描述：

● try 块用于包含可能引发异常的代码。
● throw 用于抛出异常。
● catch 块用于捕获并处理异常。
*/

#include<iostream>
#include<stdexcept>
#include<vector>
using namespace std;

// 函数，计算除法
double divide(double numerator, double denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero."); // 抛出异常
    }
    return numerator / denominator;
}

// 函数，抛出异常
void func1() {
    throw std::runtime_error("Error in func1.");
}

// 函数，调用 func1 并重新抛出异常
void func2() {
    try {
        func1();
    } catch (...) { // 捕获所有异常
        std::cout << "func2() caught an exception and is rethrowing it." << std::endl;
        throw; // 重新抛出当前异常
    }
}

void demo() {
    double num, denom;
    std::cout << "enter a numerator: ";
    std::cin >> num;
    std::cout << "enter a denominator: ";   
    std::cin >> denom;
    try {
        double result = divide(num, denom);
        std::cout << "result = " << result << std::endl;
    } catch (const std::invalid_argument& e) {   // 捕获 std::invalid_argument 异常
        std::cout << "Error: " << e.what() << std::endl;
    }
    std::cout << "Program continues after try-catch." << std::endl;

    // 模拟不同类型的异常
    {
        try {
            // 模拟不同类型的异常
            int choice;
            std::cout << "Choose exception to throw (1: bad_alloc, 2: invalid_argument): ";
            std::cin >> choice;

            if (choice == 1) {
                throw std::bad_alloc();
            } else if (choice == 2) {
                throw std::invalid_argument("Invalid argument provided.");
            } else {
                std::cout << "No exception thrown." << std::endl;
            }
        } catch (std::bad_alloc &e) { // 处理 bad_alloc 异常
            std::cerr << "Caught std::bad_alloc: " << e.what() << std::endl;
        } catch (std::invalid_argument &e) { // 处理 invalid_argument 异常
            std::cerr << "Caught std::invalid_argument: " << e.what() << std::endl;
        }

        std::cout << "Program continues after try-catch." << std::endl;
    }

    // 可以在 catch 块中使用 throw 语句重新抛出捕获的异常，以便其他部分处理。
    {
        try {
            func2();
        } catch (std::exception& e) {
            std::cout << "Main caught: " << e.what() << std::endl;
        }
    }
}

// Exercise

/*
打印九九乘法表
题目描述
编写一个 C++ 程序，使用嵌套的 for 循环来打印标准的九九乘法表。输出的格式应整齐对齐，便于阅读。
*/

void ex1()
{
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j <= i; j++) {
            cout << i << "*" << j << '=' << i*j << '\t';
        }
        cout << endl;
    }
}

/*
实现冒泡排序
题目描述
编写一个 C++ 程序，使用 冒泡排序算法 对用户输入的一组整数进行排序。冒泡排序是一种简单的排序算法，通过重复交换相邻的未按顺序排列的元素，将最大或最小的元素“冒泡”到序列的一端。
*/

// 冒泡排序函数
void bubbleSort(int arr[], int n) {
    bool flag = true;
    for (int i = 0; i < n; i++) {
        flag = true;
        for (int j = n - 1; j > i; j--) {
            if (arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
                flag = false;
            }
        }
        if (flag) return;
    }
}

// 打印数组函数
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void ex2()
{
    int n;
    
    // 获取数组大小
    std::cout << "请输入整数的数量: ";
    std::cin >> n;
    
    if (n <= 0) {
        std::cerr << "错误：数组大小必须为正整数。" << std::endl;
        return;
    }
    
    int *arr = new int[n];
    
    // 获取数组元素
    std::cout << "请输入 " << n << " 个整数，用空格分隔: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    
    // 打印排序前的数组
    std::cout << "排序前的数组: ";
    printArray(arr, n);
    
    // 执行冒泡排序
    bubbleSort(arr, n);
    
    // 打印排序后的数组
    std::cout << "排序后的数组: ";
    printArray(arr, n);
    
    // 释放动态分配的内存
    delete[] arr;
}


/*
生成斐波那契数列
题目描述
编写一个 C++ 程序，生成并显示斐波那契数列。程序应允许用户指定生成数列的长度，并使用 循环结构 或 递归方法 来生成斐波那契数。
*/

void ex3()
{
    int n;
    
    // 获取要生成的斐波那契数的数量
    std::cout << "请输入要生成的斐波那契数的数量: ";
    std::cin >> n;
    
    if (n < 0) {
        std::cerr << "错误：数量不能为负数。" << std::endl;
        return;
    }
    vector<int> nums{0, 1};
    for (int i = 2; i < n; i++)
    {
        nums.push_back(nums[i - 1] + nums[i - 2]);
    }
    
    for (int x : nums) {
        cout << x << ' ';
    }
    cout << endl;
    
}

int main()
{
    // demo();
    ex1();
    ex2();
    ex3();
    return 0;
}


