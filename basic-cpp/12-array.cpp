// 数组知识 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/wad4t88b841epskp#APE4b


#include <iostream>

// Exercise1:
/*
题目描述:
编写一个函数 my_strcpy，其功能与标准库函数 strcpy 类似，用于将源字符串复制到目标字符串中。

要求:
● 禁止使用标准库中的字符串操作函数（如 strcpy、strlen 等）。
● 函数应能够正确处理所有合法的C风格字符串，包括空字符串。
● 确保目标字符串有足够的内存来存放源字符串。
● 函数应返回目标字符串的指针
*/


// 自定义的字符串复制函数
char* my_strcpy(char* dest, const char* src) {
    // 在此实现函数逻辑
    int i;
    for (i = 0; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}


/*
题目描述:
编写一个函数 my_strcat，其功能与标准库函数 strcat 类似，用于将源字符串追加到目标字符串的末尾。

要求:
● 禁止使用标准库中的字符串操作函数（如 strcat、strlen 等）。
● 函数应能够正确处理所有合法的C风格字符串，包括空字符串。
● 确保目标字符串有足够的内存来存放追加后的字符串。
● 函数应返回目标字符串的指针
*/


// 自定义的字符串连接函数
char* my_strcat(char* dest, const char* src) {
    // 在此实现函数逻辑
    char* res = dest;

    while(*dest != '\0')
    {
        dest++;
    }

    while(*src != '\0')
    {
        *dest++ = *src++;
    }

    *dest = '\0';

    return res;
}



int main() {

    {
        const char* source = "Hello, World!";
        char destination[100]; // 确保目标有足够的空间

        my_strcpy(destination, source);

        std::cout << "Source: " << source << std::endl;
        std::cout << "Destination: " << destination << std::endl;
    }

    {
        char destination[100] = "Hello, "; // 初始内容
        const char* source = "World!";

        my_strcat(destination, source);

        std::cout << "After concatenation: " << destination << std::endl;
    }


    return 0;
}