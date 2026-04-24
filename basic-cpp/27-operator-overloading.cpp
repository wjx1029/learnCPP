// 运算符重载 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/obhnor0ny6s0z7tz#v7O0V

/*
运算符重载注意事项
1. 语义一致性：重载运算符后，其行为应与运算符的传统意义保持一致。例如，+ 应表示加法，避免引起混淆。
2. 效率：尽量避免不必要的对象拷贝，可以通过返回引用或使用移动语义提升效率。
3. 异常安全：在实现运算符重载时，考虑并处理可能的异常情况，确保程序的健壮性。
4. 封装性：保持类的封装性，避免过度暴露内部细节。仅在必要时使用友元函数。
5. 返回类型：根据运算符的用途选择合适的返回类型。例如，算术运算符通常返回新对象，赋值运算符返回引用等。
6. 避免复杂的逻辑：运算符重载应简洁明了，不应包含过于复杂的逻辑，避免使代码难以理解和维护。
7. 可读性：使用适当的注释和文档说明运算符重载的行为，增强代码的可读性。
*/

// 综合案例：复数（Complex）类中的所有运算符重载
#include <iostream>
#include <stdexcept>
#include <cmath>


class Complex {
private:
    double real;
    double imag;
public:

    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real * other.imag + other.real * imag);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0.0) {
            throw std::runtime_error("Division by zero");
        }

        return Complex((real * other.real + imag * other.imag) / denominator, (imag * other.real - real * other.imag) / denominator);   
    }

    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }

    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imag -= other.imag;
        return *this;
    }

    Complex& operator*=(const Complex& other) {
        double tempReal = real * other.real - imag * other.imag;
        double tempImag = real * other.imag + other.real * imag;
        real = tempReal;
        imag = tempImag;
        return *this;
    }

    Complex& operator/=(const Complex& other) {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0.0) {
            throw std::runtime_error("Division by zero");
        }

        double tempReal = (real * other.real + imag * other.imag) / denominator;
        double tempImag = (imag * other.real - real * other.imag) / denominator;
        real = tempReal;
        imag = tempImag;
        return *this;
    }

    friend bool operator==(const Complex& a, const Complex& b) {
        return a.real == b.real && a.imag == b.imag;
    }

    friend bool operator!=(const Complex& a, const Complex& b) {
        return !(a == b);
    }

    friend bool operator<(const Complex& a, const Complex& b) {
        double aMag = std::sqrt(a.real * a.real + a.imag * a.imag);
        double bMag = std::sqrt(b.real * b.real + b.imag * b.imag);
        return aMag < bMag;
    }

    friend bool operator>(const Complex& a, const Complex& b) {
        return b < a;
    }

    friend bool operator<=(const Complex& a, const Complex& b) {
        return !(b < a);
    }

    friend bool operator>=(const Complex& a, const Complex& b) {
        return !(a < b);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real;
        if (c.imag >= 0) {
            os << " + " << c.imag << "i";
        } else {
            os << " - " << -c.imag << "i";
        }
        os << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Complex& c) {
        is >> c.real >> c.imag;
        return is;
    }

    Complex operator~() const {
        return Complex(real, -imag);
    }

    bool operator!() const {
        return real == 0.0 && imag == 0.0;
    }

    double& operator[](int index) {
        if (index == 0) {
            return real;
        } else if (index == 1) {
            return imag;
        } else {
            throw std::out_of_range("Index out of range for Complex.");
        }
    }
     
    const double& operator[](int index) const {
        if (index == 0) {
            return real;
        } else if (index == 1) {
            return imag;
        } else {
            throw std::out_of_range("Index out of range for Complex.");
        }
    }   

    Complex& operator++() {
        real++;
        imag++;
        return *this;
    }

    Complex& operator--() {
        real--;
        imag--;
        return *this;
    }

    Complex operator++(int) {
        Complex temp = *this;
        real++;
        imag++;
        return temp;
    }

    Complex operator--(int) {
        Complex temp = *this;
        real--;
        imag--;
        return temp;
    }

    double operator() (const std::string& part) const {
        if (part == "real") {
            return real;
        } else if (part == "imag") {
            return imag;
        } else {
            throw std::out_of_range("Invalid part for Complex.");
        }
    }   
};

int main() {
    Complex c1(3.0, 4.0);
    Complex c2(1.5, -2.5);
    Complex c3;

    // 赋值运算
    c3 = c1;
    std::cout << "c3 = " << c3 << std::endl;

    // 加法
    Complex c4 = c1 + c2;
    std::cout << "c1 + c2 = " << c4 << std::endl;

    // 减法
    Complex c5 = c1 - c2;
    std::cout << "c1 - c2 = " << c5 << std::endl;

    // 乘法
    Complex c6 = c1 * c2;
    std::cout << "c1 * c2 = " << c6 << std::endl;

    // 除法
    try {
        Complex c7 = c1 / c2;
        std::cout << "c1 / c2 = " << c7 << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    // 比较运算
    if (c1 > c2)
        std::cout << "c1 的模长大于 c2" << std::endl;
    else
        std::cout << "c1 的模长不大于 c2" << std::endl;

    // 逻辑非运算
    Complex c_zero;
    if (!c1)
        std::cout << "c1 是零复数" << std::endl;
    else
        std::cout << "c1 不是零复数" << std::endl;

    if (!c_zero)
        std::cout << "c_zero 是零复数" << std::endl;
    else
        std::cout << "c_zero 不是零复数" << std::endl;

    // 取反运算
    Complex c_neg = ~c1;
    std::cout << "~c1 = " << c_neg << std::endl;

    // 下标运算
    try {
        std::cout << "c1[0] (real) = " << c1[0] << std::endl;
        std::cout << "c1[1] (imag) = " << c1[1] << std::endl;
        // std::cout << "c1[2] = " << c1[2] << std::endl; // 会抛出异常
    } catch (const std::out_of_range& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    // 自增自减运算符
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "++c1 = " << ++c1 << std::endl;
    std::cout << "c1++ = " << c1++ << std::endl;
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "--c1 = " << --c1 << std::endl;
    std::cout << "c1-- = " << c1-- << std::endl;
    std::cout << "c1 = " << c1 << std::endl;

    // 函数调用运算符
    std::cout << "c1 的实部: " << c1("real") << std::endl;
    std::cout << "c1 的虚部: " << c1("imag") << std::endl;

    // 输入运算
    std::cout << "请输入一个复数的实部和虚部，以空格分隔: ";
    Complex c_input;
    std::cin >> c_input;
    std::cout << "您输入的复数是: " << c_input << std::endl;

    return 0;
}