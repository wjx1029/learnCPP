// 运算符 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/kytb9xp8h93wxg3w

# include<iostream>
# include<bitset>
# include<ostream>
# include<vector>

using namespace std;

class Complex {
public:
    double real, imag;
    
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // 重载 + 运算符
    Complex operator+(const Complex &c) {
        return Complex(real + c.real, imag + c.imag);
    }
    
    // 重载 << 运算符（作为友元函数）
    friend ostream& operator<<(ostream &out, const Complex &c);
};

ostream& operator<<(ostream &out, const Complex &c) {
    out << c.real << " + " << c.imag << "i";
    return out;
}

// Exercise

/*
1 交换两个数
题目： 使用位运算符，交换两个整数变量的值而不使用第三个变量
*/

void ex1()
{
    int a = 5;
    int b = 3;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    a ^= b;
    b ^= a;
    a ^= b;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

/*
2 函数修改外部变量
题目： 编写一个函数，接受一个整数指针，使用解引用运算符修改其值为原值的平方。
*/

void ex2(int *p)
{
    cout << "a = " << *p << endl;
    *p = *p * *p;
    cout << "a = " << *p << endl;
}

/*
计算范围内所有元素的和
题目： 编写一个函数，接受 std::vector<int> 的迭代器范围，计算并返回范围内所有元素的和。
*/

int ex3(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    int sum = 0;
    for(std::vector<int>::iterator i = begin; i != end; i++)
    {
        sum += *i;
    }
    return sum;
}



int main()
{
    int a = 5;  // 二进制：0101
    int b = 3;  // 二进制：0011
    int andResult = a & b; // 1 (0001)
    int orResult = a | b;  // 7 (0111)
    int xorResult = a ^ b; // 6 (0110)
    int notResult = ~a;    // -6 (补码)
    int leftShift = a << 1; // 10 (1010)
    int rightShift = a >> 1; // 2 (0010)
    //显示二进制结果
    std::cout << "a & b = " << andResult << " (binary: " << std::bitset<4>(andResult) << ")" << std::endl;
    std::cout << "a | b = " << orResult << " (binary: " << std::bitset<4>(orResult) << ")" << std::endl;
    std::cout << "a ^ b = " << xorResult << " (binary: " << std::bitset<4>(xorResult) << ")" << std::endl;
    std::cout << "~a = " << notResult << " (binary: " << std::bitset<32>(notResult) << ")" << std::endl;
    std::cout << "a << 1 = " << leftShift << " (binary: " << std::bitset<4>(leftShift) << ")" << std::endl;
    std::cout << "a >> 1 = " << rightShift << " (binary: " << std::bitset<4>(rightShift) << ")" << std::endl;

    // 复数加法
    std::cout << "复数加法:" << std::endl;
    Complex c1(1.2, 3.4);
    Complex c2(5.6, 7.8);
    Complex c3 = c1 + c2;
    std::cout << "c1 + c2 = " << c3 << std::endl; // 输出: c1 + c2 = 6.8 + 11.2i

    
    ex1();
    ex2(&a);
    std::vector<int> numbers = {2, 4, 6, 8, 10};
    int total = ex3(numbers.begin(), numbers.end());
    std::cout << "Sum: " << total << std::endl;

    return 0;
}