// 多维数组 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/phthnv9ye6i7yqy5

#include<iostream>

using namespace std;

/*
题目描述
编写一个C++程序，输入两个2x3的矩阵，计算它们的和，并输出结果矩阵。
*/

void ex1()
{
    int a1[2][3] = {1, 2, 3, 4, 5, 6};
    int a2[2][3] = {7, 8, 9, 10, 11, 12};
    int a3[2][3];
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            a3[i][j] = a1[i][j] + a2[i][j];
        }
    }
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cout << a3[i][j] << " ";
        }
        cout << endl;
    }
}

/*
题目描述
编写一个C++程序，输入一个3x3的矩阵，计算其转置矩阵，并输出结果。
*/

void ex2()
{
    const int SIZE = 3;
    int matrix[SIZE][SIZE];
    int transpose[SIZE][SIZE];

    // 输入原始矩阵
    std::cout << "请输入一个3x3矩阵的元素（共9个整数）:" << std::endl;
    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            // 在此输入matrix[i][j]
            cin >> matrix[i][j];
        }
    }

    // 计算转置矩阵
    // 在此实现转置逻辑
    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            transpose[j][i] = matrix[i][j];
        }
    }

    // 输出转置后的矩阵
    std::cout << "矩阵的转置为:" << std::endl;
    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            // 在此输出transpose[i][j]
            cout << transpose[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


int main()
{
    ex1();
    ex2();
    return 0;
}
