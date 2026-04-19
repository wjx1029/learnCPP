// const用法 ：https://www.yuque.com/lianlianfengchen-cvvh2/zack/sqhwkaa0ti9g64d8


# include <iostream>

constexpr int add(int a, int b) {
    return a + b;
}

int global_i = 10;

int main()
{
    int a = 10;
    // const and pointer
    // 1. 常量指针 - (指针指向的内容不能改)
    /*
    *p1 是常量 → 不能通过 p1 修改值
    p1 本身可以变 → 可以指向别的地址
    */
    const int *p1;

    // 2. 指针常量（指针本身是常量）
    /*
    p2 是常量 → 不能改指向
    *p2 可以改 → 可以修改值
    */
   int * const p2 = &a;

   // 3. 常量指针常量（都不能改）
   /*
    不能改指向
    不能改值
   */
    const int * const p3 = &a;

    /*
        写法	                含义	             类型
    const int a	a           本身不能改	         ✅ 顶层 const
    int * const p	        p 不能改指向	     ✅ 顶层 const
    const int * p	       不能通过 p 改值	     ✅ 底层 const
    const int * const p	      两者都有	         ✅ 顶层 + 底层
    */


    // constexpr（核心关键字）
    // ✅ 定义 : 声明一个变量或函数，使其必须可以在编译期求值

    // constexpr function
    // ✅ 定义 : 可以在编译期执行的函数,也可以运行期执行



    constexpr int x = add(2, 3);

    // Exercise :
    // global_i是一个全局变量，下面这个指针是什么类型？能否修改cp指向的数据的内容(*cp = 200)？

    constexpr const int * cp = &global_i;

    // Answer :
    // cp 是一个指向const int 类型的指针constexpr指针，等价于 const int * const cp
    // 即不能修改cp的指向，也不能修改cp指向的内容
    // constexpr 保证“指针本身”不可变，const（在 * 左边）保证“指向内容”不可变


}