// 模板的练习题

#include <iostream>
#include <string>
#include <vector>
#include <concepts>

/*
练习 1：实现一个通用的 Swap 函数模板
要求：
● 编写一个函数模板 swapValues，可以交换任意类型的两个变量。
● 在 main 函数中测试 int、double、std::string 类型的交换。
*/
template <typename T>
void Swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

void ex1() {
    int a = 10;
    int b = 20;
    std::cout << "a = " << a << ", b = " << b << std::endl;
    Swap(a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;

    double c = 3.14;
    double d = 2.7185;
    std::cout << "c = " << c << ", d = " << d << std::endl;
    Swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;

    std::string e = "hello";
    std::string f = "world";
    std::cout << "e = " << e << ", f = " << f << std::endl;
    Swap(e, f);
    std::cout << "e = " << e << ", f = " << f << std::endl;
}

/*
练习 2：实现一个模板类 Triple，存储三个相同类型的值，并提供获取各个成员的函数。
要求：
● 模板参数为类型 T。
● 提供构造函数、成员变量及访问函数。
● 在 main 中实例化 Triple<int> 和 Triple<std::string>，进行测试。
*/

template <class T>
class Triple {
public:
    T a, b, c;

    Triple(T a, T b, T c) : a(a), b(b), c(c) {}

    T operator[](int index) {
        return (index == 0) ? a : (index == 1) ? b : c;
    }

    T getA() {
        return a;
    }
    T getB() {
        return b;
    }
    T getC() {
        return c;
    }
};

void ex2() {
    Triple<int> intTriple(1, 2, 3);
    std::cout << "intTriple[0] = " << intTriple[0] << std::endl;
    std::cout << "intTriple[1] = " << intTriple[1] << std::endl;
    std::cout << "intTriple[2] = " << intTriple[2] << std::endl;
    std::cout << "intTriple.getA() = " << intTriple.getA() << std::endl;
    std::cout << "intTriple.getB() = " << intTriple.getB() << std::endl;
    std::cout << "intTriple.getC() = " << intTriple.getC() << std::endl;

    Triple<std::string> strTriple("a", "b", "c");
    std::cout << "strTriple[0] = " << strTriple[0] << std::endl;
    std::cout << "strTriple[1] = " << strTriple[1] << std::endl;
    std::cout << "strTriple[2] = " << strTriple[2] << std::endl;
    std::cout << "strTriple.getA() = " << strTriple.getA() << std::endl;
    std::cout << "strTriple.getB() = " << strTriple.getB() << std::endl;
    std::cout << "strTriple.getC() = " << strTriple.getC() << std::endl;
}

/*
练习 3：使用模板特化，为类模板 Printer 提供针对 bool 类型的全特化，实现专门的输出格式。
要求：
● 通用模板类 Printer，具有 print 函数，输出 General Printer: value。
● 全特化 Printer<bool>，输出 Boolean Printer: true 或 Boolean Printer: false
*/

template <class T>
class Printer {
public:
    void operator()(T value) {
        std::cout << "General Printer: " << value << std::endl;
    }
};

template<>
class Printer<bool> {
public:
    void operator()(bool value) {
        std::cout << std::boolalpha << "Bool Printer: " << value << std::endl;
    }
};

void ex3() {
    Printer<int> intPrinter;
    intPrinter(10);

    Printer<bool> boolPrinter;
    boolPrinter(true);
}

/*
练习 4：实现一个变参模板函数 logMessages，可以接受任意数量和类型的参数，并依次打印它们。
要求：
● 使用递归方法实现。
● 在 main 中测试不同参数组合的调用。
*/

// no arguments
void logMessages() {
    std::cout << std::endl;
}

// multiple arguments
template <typename T, typename... Args>
void logMessages(const T& value, const Args&... args) {
    std::cout << value << " ";
    logMessages(args...);
}

void ex4() {
    logMessages();
    logMessages(10, 20, 30);
    logMessages("hello", "world", true);
    logMessages(10.5, 'a', 30, "hello", false, 100);
}

/*
练习 5：编写模板元编程结构 IsPointer, 用于在编译期判断一个类型是否为指针类型。
要求：
● 定义 IsPointer<T>，包含 value 静态常量成员，值为 true 或 false。
● 使用特化进行实现。
● 在 main 中使用 static_assert 进行测试
*/

template <class T>
class IsPointer {
public:
    static constexpr bool value = false;
};

template <class T>
class IsPointer<T*> {
public:
    static constexpr bool value = true;
};

void ex5() {
    static_assert(!IsPointer<int>::value, "int is not a pointer");
    static_assert(IsPointer<int*>::value, "int* is a pointer");
}

/*

*/
template <typename T, typename = void>
struct has_size_method : std::false_type {};

template <typename T>
struct has_size_method<T, std::void_t<decltype(std::declval<T>().size())>> : std::true_type {};


template <typename T>
typename std::enable_if<has_size_method<T>::value, void>::type
enableIfExample(const T& container) {
    std::cout << "Container has size: " << container.size() << std::endl;
}

void ex6() {
    std::vector<int> vec = {1, 2, 3};
    int a;
    enableIfExample(vec);
    // enableIfExample(a);

    static_assert(has_size_method<std::vector<int>>::value, "vector 应该有 size()");
    static_assert(!has_size_method<int>::value, "int 不应该有 size()");
}

/*
练习 7：使用 C++20 Concepts，定义一个 Concept Integral，要求类型必须是整型，并使用该 Concept 约束一个函数模板 isEven，判断传入的整数是否为偶数。
要求：
● 定义 Integral Concept。
● 编写函数模板 isEven(u)，仅接受满足 Integral 的类型。
● 在 main 中测试不同类型的调用。
*/

template <typename T>
concept Integral = std::is_integral_v<T>;

template<Integral T>
bool isEven(T value) {
    return value % 2 == 0;
}

void ex7() {
    std::cout << std::boolalpha; // 将 bool 输出为 true/false
    std::cout << "isEven(4) = " << isEven(4) << std::endl;
    std::cout << "isEven(5) = " << isEven(5) << std::endl;
    // 错误调用：浮点型（取消注释会导致编译报错）
    // double c = 10.5;
    // std::cout << isEven(c) << std::endl; 
    // 错误调用：字符串（取消注释会导致编译报错）
    // std::cout << isEven("hello") << std::endl;
}

/*
练习 8：实现一个固定大小的栈（FixedStack）类模板，支持多种数据类型和指定大小。使用非类型模板参数指定栈的大小。
要求：
● 模板参数为类型 T 和 std::size_t N。
● 提供 push, pop, top 等成员函数。
● 在 main 中测试 FixedStack<int, 5> 和 FixedStack<std::string, 3>。
*/

template<typename T, std::size_t N>
class FixedStack {
public:
    T data[N];
    std::size_t top = 0;

    void push(T value) {
        if (top < N) {
            data[top++] = value;
        }
    }

    void pop() {
        if (top > 0) {
            top--;
        }
    }

    T& getTop() {
        if (top > 0) {
            return data[top - 1];
        } else {
            throw std::runtime_error("Stack is empty");
        }
    }

    const T& getTop() const {
        return getTop();
    }
};

void ex8() {
    FixedStack<int, 5> intStack;
    FixedStack<std::string, 3> strStack;

    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    std::cout << "intStack top: " << intStack.getTop() << std::endl;
    intStack.pop();
    std::cout << "intStack top: " << intStack.getTop() << std::endl;

    strStack.push("hello");
    strStack.push("world");
    strStack.push("cpp");

    std::cout << "strStack top: " << strStack.getTop() << std::endl;
    strStack.pop();
    std::cout << "strStack top: " << strStack.getTop() << std::endl;

}

/*
练习 9：实现一个模板类 TypeIdentity，其成员类型 type 等同于模板参数 T。并使用 static_assert 检查类型关系。
要求：
● 定义 TypeIdentity<T>，包含类型成员 type。
● 使用 std::is_same 与 static_assert 验证。
示例：
static_assert(std::is_same<TypeIdentity<int>::type, int>::value, "TypeIdentity<int> should be int");
*/
template <class T>
class TypeIdentity {
public:
    using type = T;
};

void ex9() {
    static_assert(std::is_same<TypeIdentity<int>::type, int>::value, "TypeIdentity<int> should be int");
    static_assert(std::is_same<TypeIdentity<std::string>::type, std::string>::value, "TypeIdentity<std::string> should be std::string");
    static_assert(std::is_same<TypeIdentity<double>::type, double>::value, "TypeIdentity<double> should be double");
    static_assert(std::is_same<TypeIdentity<void>::type, void>::value, "TypeIdentity<void> should be void");
}

/*
练习 10：编写一个模板元编程结构 LengthOf, 用于在编译期计算类型列表的长度。
要求：
● 使用 TypeList 模板定义类型列表。
● 定义 LengthOf<TypeList<...>>::value 表示类型列表的长度。
● 在 main 中使用 static_assert 进行测试。
*/

template <typename... Ts>
struct TypeList {};

template <typename List>
struct LengthOf;

template <typename... Ts>
struct LengthOf<TypeList<Ts...>> {
    static constexpr std::size_t value = sizeof...(Ts);
};

void ex10() {
    static_assert(LengthOf<TypeList<int, std::string, double, void>>::value == 4, "LengthOf<TypeList<int, std::string, double, void>> should be 4");
    static_assert(LengthOf<TypeList<int, std::string, double>>::value == 3, "LengthOf<TypeList<int, std::string, double>> should be 3");
    static_assert(LengthOf<TypeList<int, std::string>>::value == 2, "LengthOf<TypeList<int, std::string>> should be 2");
    static_assert(LengthOf<TypeList<int>>::value == 1, "LengthOf<TypeList<int>> should be 1");
    static_assert(LengthOf<TypeList<>>::value == 0, "LengthOf<TypeList<>> should be 0");
    std::cout << "所有 LengthOf 测试通过！" << std::endl;
}



int main() {
    // ex1();
    // ex2();
    // ex3();
    // ex4();
    // ex5();
    // ex6();
    // ex7();
    // ex8();
    // ex9();
    ex10();

    return 0;
}
