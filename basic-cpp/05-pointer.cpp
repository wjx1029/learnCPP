// 指针 ：https://www.yuque.com/lianlianfengchen-cvvh2/zack/cw61ttu5rwmmbc9l

#include <iostream>

int main()
{
    // 符号的多重含义
    int ival2 = 42;
    //& 紧跟着类型名出现，因此是声明的一部分，r是一个引用
    int &r = ival2;
    //* 紧跟着类型名出现，因此是声明的一部分，p是一个指针
    int *p;
    // &出现在表达式中，是一个取地址符号
    p = &ival2;
    // * 出现在表达式中，是一个解引用符号
    *p = ival2;
    //& 是声明的一部分，*是一个解引用符号
    int &r2 = *p;


    // 空指针定义方式
    // C++11 最推荐方式
    int *p1 = nullptr;
    // 直接将p2初始化为字面量0
    int *p2 = 0;
    // 需要使用#include<cstdlib>
    // 等价于int * p3 = 0;
    int *p3 = NULL;
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    std::cout << "p3: " << p3 << std::endl;


    // 以指针为例，指针是内存中的对象，像其他对象一样也有自己的地址，
    // 因此允许把指针的地址再存放到另一个指针当中。通过＊的个数可以区分指针的级别。
    // 也就是说，＊＊表示指向指针的指针，＊＊＊表示指向指针的指针的指针，以此类推：
    int ival4 = 1024;
    // pival4指向了int型的数
    int *pival4 = &ival4;
    // ppi指向了一个int型的指针
    int **ppi = &pival4;

    std::cout << "The value of ival\n"
              << "direct value: " << ival4 << "\n"
              << "indirect value: " << *pival4 << "\n"
              << "doubly indirect value : " << **ppi
              << std::endl;



    // 引用本身不是一个对象，因此不能定义指向引用的指针。
    // 但指针是对象，所以存在对指针的引用
    int init = 42;
    // pinit是一个int型的指针
    int *pinit;
    // rpinit是一个对指针pinit的引用
    int *& rpinit = pinit;
    // rpinit引用了一个指针，因此给rpinit赋值&init就是令pinit指向init
    rpinit = &init;
    // 解引用rpinit得到i,也就是p指向的对象，将init改为0
    *rpinit = 0;
    std::cout << *rpinit << std::endl;
    std::cout << *pinit << std::endl;
}