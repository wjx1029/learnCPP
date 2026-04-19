// 类型推导和别名 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/vi0tk5zuz6eqevcu#qpgzL

# include <iostream>

int main()
{
    // 别名

    typedef double wages;       // wages 是double的同义词
    typedef wages base, *p;     // base是double的同义词,p是double*的同义词

    using int64_t = long long;

    // 类型推导

{   
    // auto 忽略顶层 const，保留底层 const
    const int a = 10;
    auto b = a;   // int（const 被丢掉）
    const int *p = &a;
    auto q = p;   // const int *

    // 引用会被忽略
    int a1 = 10;
    int &r = a1;
    auto x = r;   // int（引用被去掉）

    // 保留引用或const
    auto &x1 = r;  // int&
    const auto x2 = a; // const int
}

{   
    // 变量名 → 原类型（包括 const / 引用）
    const int a = 10;
    decltype(a) b = 20;  // const int

    // 表达式 → 可能变引用（关键坑点）
    // a → int
    // (a) → 表达式 → 左值 → 推导为引用
    int a1 = 10;
    decltype((a1)) b1 = a1;  // int&

    /*  decltype 的三条黄金法则：
    1️⃣ decltype(变量名) → 原类型（含 const / 引用）
    2️⃣ decltype(表达式)：
        - 左值 → T&
        - 右值 → T
    3️⃣ 多一层括号，结果可能完全变
    */

    // auto：用“值”推导类型（类似模板参数推导）
    // decltype：用“表达式形式”推导类型（精确保留类型信息）

}



}