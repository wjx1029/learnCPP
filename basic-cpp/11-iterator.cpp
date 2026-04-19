// 迭代器 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/vm0al3l8ikglhop3


#include<iostream>
#include<vector>

void ex1()      // 编写一个程序，读取一组整数到一个 std::vector 中，并打印每对相邻元素的和
{
    int n;
    std::vector<int> vec;
    std::cin >> n;
    while(n--)
    {
        int x;
        std::cin >> x;
        vec.push_back(x);
    }

    if (vec.size() == 1) std::cout << vec[0] << std::endl;
    else
    {
        for (auto i = vec.begin(), j = vec.begin() + 1; j != vec.end(); i++, j++)
        {
            std::cout << *i + *j << ' ';
        }
        std::cout << std::endl;
    }
}


void ex2()      // 编写一个程序，从用户输入一组整数到一个 std::vector 中，然后使用迭代器反向打印这些元素。
{
    int n;
    std::vector<int> vec;
    std::cin >> n;
    while(n--)
    {
        int x;
        std::cin >> x;
        vec.push_back(x);
    }

    for (auto it = vec.rbegin(); it != vec.rend(); it++)
    {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}


void ex3()      //  编写一个程序，创建两个 std::vector，从用户输入填充它们。使用迭代器将这两个 vector 合并为一个新 vector
{
    std::vector<int> v1, v2, v;
    int x;
    std::cout << "请输入第一个向量的整数(输入-1结束): \n";
    while(std::cin >> x && x != -1)
    {
        v1.push_back(x);
    }
    std::cout << "请输入第二个向量的整数(输入-1结束): \n";
    while(std::cin >> x && x != -1)
    {
        v2.push_back(x);
    }

    v.insert(v.end(), v1.begin(), v1.end());
    v.insert(v.end(), v2.begin(), v2.end());

    for (auto num : v)
    {
        std::cout << num << ' ';
    }
    std::cout << std::endl;
}


int main()
{
    // ex1();
    // ex2();
    ex3();

    return 0;
}