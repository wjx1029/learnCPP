// 继承和多态 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/ip4cgg8ihlnykgpd
// https://www.yuque.com/lianlianfengchen-cvvh2/zack/pi088g754xnqfcwz

#include <iostream>
#include <string>

using namespace std;

/*
1. 简单继承与成员访问
题目：
定义一个基类 Person，包含以下成员：
● 私有成员变量：name（字符串类型），age（整数类型）
● 公共成员函数：
  ○ 构造函数：接受姓名和年龄作为参数并初始化成员变量
  ○ displayInfo()：打印姓名和年龄

然后，定义一个派生类 Student，继承自 Person，并添加以下内容：
● 私有成员变量：studentID（字符串类型）
● 公共成员函数：
  ○ 构造函数：接受姓名、年龄和学号作为参数，并调用基类构造函数初始化姓名和年龄
  ○ 重写 displayInfo()：除了显示姓名和年龄外，还显示学号

要求：
● 在 main 函数中，创建一个 Student 对象，并调用 displayInfo() 函数展示信息。
*/

class Person
{
private:
    string name_;
    int age_;
public:
    Person(string name, int age): name_(name), age_(age) {}
    void displayInfo() {
        cout << "Name: " << name_ << ", Age: " << age_ << endl;
    }
    string getname() const { return name_; }
    int getage() const { return age_; }
};

class Student: public Person
{
private:
    string StudentID_;
public:
    Student(string name, int age, string studentID):
        Person(name, age), StudentID_(studentID) {}
    void displayInfo() {
        cout << "Name: " << getname() << ", Age: " << getage() << ", Student ID: " << StudentID_ << endl;
    }
};

void ex1() {
    Student student("张三", 18, "2023001");
    student.displayInfo();
}


/*
2. 虚函数重写与多态性
题目：
定义一个基类 Shape，包含以下内容：
● 公共成员函数：
  ○ 虚函数 draw()：在基类中实现，输出 "Drawing a generic shape."

然后，定义两个派生类 Circle 和 Rectangle，分别重写 draw() 函数，实现各自的输出：
● Circle 的 draw() 输出："Drawing a circle."
● Rectangle 的 draw() 输出："Drawing a rectangle."

要求：
● 在 main 函数中，创建一个 Shape 类型的指针数组，包含不同类型的 Shape 对象（Circle 和 Rectangle）。
● 遍历数组，调用每个对象的 draw() 函数，验证多态性的实现。
*/

class Shape
{
public:
    virtual void draw() {
        cout << "Drawing a generic shape." << endl;
    }
    virtual ~Shape() {cout << "Shape destructor called." << endl;}
};

class Circle: public Shape
{
public:
    void draw() override {
        cout << "Drawing a circle." << endl;
    }
};

class Rectangle: public Shape
{
public:
    void draw() override {
        cout << "Drawing a rectangle." << endl;
    }
};

void ex2()
{
    Shape * ptr_shapes[3] = {new Circle(), new Rectangle(), new Shape()};
    for (int i = 0; i < 3; i++) {
        ptr_shapes[i]->draw();
    }
    for (int i = 0; i < 3; i++) {
        delete ptr_shapes[i];
    }
}

/*
3. 函数重载与隐藏
题目：
定义一个基类 Calculator，包含以下公共成员函数：
● int add(int a, int b)：返回两个整数的和
● double add(double a, double b)：返回两个浮点数的和

然后，定义一个派生类 AdvancedCalculator，继承自 Calculator，并添加以下成员函数：
● int add(int a, int b, int c)：返回三个整数的和
*/

class Calculator
{
public:
    virtual int add(int a, int b) {return a + b;}
    virtual double add(double a, double b) {return a + b;}
};
// 在 C++ 中，如果派生类（AdvancedCalculator）定义了一个与基类（Calculator）同名但参数列表不同的函数，
// 基类中所有同名的重载函数在派生类的作用域内都会被遮蔽（Hidden），而不是自动与之构成重载。
// AdvancedCalculator 定义了 add(int, int, int)。
// 这会导致基类中的 add(int, int) 和 add(double, double) 在 AdvancedCalculator 的对象中不可见
class AdvancedCalculator: public Calculator
{
public:
    using Calculator::add;  // using 声明将它们引入派生类的作用域：
    int add(int a, int b, int c) {return a + b + c;}
};
// 重载 (Overloading)：在同一作用域内。
// 重写 (Overriding)：派生类覆盖基类的 virtual 函数（参数必须完全一致）。
// 遮蔽 (Hiding)：派生类定义了同名函数，导致基类同名函数在子类作用域失效。
void ex3()
{
    AdvancedCalculator calculator;
    cout << calculator.add(1, 2, 3) << endl;
    cout << calculator.add(2, 4) << endl;
    cout << calculator.add(2.5, 3.5) << endl;
}

/*
4. 抽象类与纯虚函数
题目：
定义一个抽象基类 Animal，包含以下内容：
● 公共纯虚函数：
  ○ void makeSound() const：纯虚函数，用于发出动物的叫声

然后，定义两个派生类 Dog 和 Cat，分别实现 makeSound() 函数：
● Dog 的 makeSound() 输出："Woof!"
● Cat 的 makeSound() 输出："Meow!"

要求：
● 在 main 函数中，创建 Dog 和 Cat 对象的基类指针，并调用 makeSound() 函数，展示多态性。
*/

class Animal
{
public:
    virtual void makeSound() const = 0;
    virtual ~Animal() {cout << "Animal destructor called." << endl;}
};

class Dog: public Animal
{
public:
    void makeSound() const override {
        cout << "Woof!" << endl;
    }
};

class Cat: public Animal
{
public:
    void makeSound() const override {
        cout << "Meow!" << endl;
    }
};

void ex4()
{
    Animal *ptr_dog = new Dog();
    ptr_dog->makeSound();


    Animal *ptr_cat = new Cat();
    ptr_cat->makeSound();

    delete ptr_dog;
    delete ptr_cat;
}

/*
构造函数与析构函数的继承
题目：
定义一个基类 Vehicle，包含以下内容：
● 公共成员函数：
  ○ 构造函数：输出 "Vehicle constructed."
  ○ 析构函数：输出 "Vehicle destructed."

然后，定义一个派生类 Car，继承自 Vehicle，并添加以下内容：
● 公共成员函数：
  ○ 构造函数：输出 "Car constructed."
  ○ 析构函数：输出 "Car destructed."

要求：
● 在 main 函数中，创建一个 Car 对象，并观察构造和析构的调用顺序。
*/

class Vehicle
{
public:
    Vehicle() {cout << "Vehicle constructed." << endl;}
    ~Vehicle() {cout << "Vehicle destructed." << endl;}
};

class Car: public Vehicle
{
public:
    Car() {cout << "Car constructed." << endl;}
    ~Car() {cout << "Car destructed." << endl;}
};

void ex5()
{
    Car car;
}


int main()
{
    // ex1();
    // ex2();
    // ex3();
    // ex4();
    ex5();
    return 0;
}
