// 变量和输出: https://www.yuque.com/lianlianfengchen-cvvh2/zack/xdc15ohr77kwqglu


/*
练习:
定义初始化一个变量pai_val数值为 3.14， 初始化一个int类型的变量int_val变量值为5，分别输出这两个变量的值。
初始化一个bool变量数值为-100，输出bool变量的值，看看是true还是false。
*/

#include <iostream>
using namespace std;

int main()
{
    double pai_val = 3.14;
    int int_val = 5;
    bool flag = -100;

    cout << "pai_val=" << pai_val << endl;
    cout << "int_val=" << int_val << endl;
    cout << "flag=" << flag << endl;
    cout << boolalpha << "flag=" << flag << endl;
    cout << "flag=" << flag << endl;
    
    return 0;
}