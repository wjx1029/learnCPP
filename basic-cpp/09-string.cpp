// string字符串 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/kq7w8g0menfsdyd7

#include <iostream>
#include <string>
#include <sstream>

int main() {

    // 读取包含空格的整行字符串：
    // {   
    //     std::string line;
    //     std::cout << "请输入一行文本：";
    //     std::getline(std::cin, line);                           
    //     std::cout << "您输入的文本是：" << line << std::endl;
    // }

    // 用 find() 查找子字符串：
    {
        std::string text = "The quick brown fox jumps over the lazy dog.";
        std::string word = "fox";

        size_t pos = text.find(word);
        if (pos != std::string::npos) {
            std::cout << "找到 '" << word << "' 在位置: " << pos << std::endl;
        } else {
            std::cout << "'" << word << "' 未找到。" << std::endl;
        }
    }

    // replace() 替换字符串
    {
        std::string text = "I like cats.";
        std::string from = "cats";
        std::string to = "dogs";

        size_t pos = text.find(from);
        if (pos != std::string::npos) {
            text.replace(pos, from.length(), to);
            std::cout << "替换后: " << text << std::endl; // 输出: I like dogs.
        } else {
            std::cout << "'" << from << "' 未找到。" << std::endl;
        }
    }

    // 使用 at() 函数（包含边界检查）
    {
        std::string str = "ABCDE";
        try {
            char c = str.at(10); // 超出范围，会抛出异常
        } catch (const std::out_of_range& e) {
            std::cout << "异常捕获: " << e.what() << std::endl;
        }
    }
    
    // erase()：删除字符串的部分内容。
    {
        std::string str = "Hello, World!";
        str.erase(5, 7); // 从位置5开始，删除7个字符
        std::cout << str << std::endl; // 输出: Hello!
    }

    // insert()：在指定位置插入字符串或字符。
    {
        std::string str = "Hello World";
        str.insert(5, ",");
        std::cout << str << std::endl; // 输出: Hello, World
    }

    // find_first_of(), find_last_of()：查找字符集合中的任何一个字符。
    {
        std::string str = "apple, banana, cherry";
        size_t pos = str.find_first_of(", ");
        std::cout << "第一个逗号或空格的位置: " << pos << std::endl; // 输出: 5
    }

    //======================= 高级用法 =============================

    // 字符串流（stringstream）
    // std::stringstream 是 C++ 标准库中第 <sstream> 头文件提供的一个类，
    // 用于在内存中进行字符串的读写操作，类似于文件流。
    {
        std::stringstream ss;
        ss << "Value: " << 42 << ", " << 3.14;

        std::string result = ss.str();
        std::cout << result << std::endl; // 输出: Value: 42, 3.14


        // 从字符串流中读取数据(将其他类型转换为 std::string)
        std::string data = "123 45.67 Hello";
        std::stringstream sss(data);

        int a;
        double b;
        std::string c;

        sss >> a >> b >> c;

        std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
        // 输出: a: 123, b: 45.67, c: Hello
    }

    // 将其他类型转换为 std::string
    {
        int num = 100;
        double pi = 3.14159;

        std::string str1 = std::to_string(num);
        std::string str2 = std::to_string(pi);

        std::cout << "str1: " << str1 << ", str2: " << str2 << std::endl;
        // 输出: str1: 100, str2: 3.141590        
    }

    // 将 std::string 转换为其他类型：
    {
        std::string numStr = "256";
        std::string piStr = "3.14";

        int num = std::stoi(numStr);
        double pi = std::stod(piStr);

        std::cout << "num: " << num << ", pi: " << pi << std::endl;
        // 输出: num: 256, pi: 3.14
    }

    // 通过 std::string 的构造函数，可以轻松将 C 风格字符串转换为 std::string
    {
        const char* cstr = "Hello, C-strings!";
        std::string str(cstr);
        std::cout << str << std::endl; // 输出: Hello, C-strings!
    }

    // 使用 c_str() 成员函数，可以获取 C 风格字符串指针
    {
        std::string str = "Hello, std::string!";
        const char* cstr = str.c_str();
        std::cout << cstr << std::endl; // 输出: Hello, std::string!
    }

    return 0;
}