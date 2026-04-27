// 常用的stream流 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/ngg46gd0emv77ng2


// 常见的流类型
// ● 标准输入流：std::cin
// ● 标准输出流：std::cout
// ● 标准错误流：std::cerr
// ● 文件输入流：std::ifstream
// ● 文件输出流：std::ofstream
// ● 文件流（读写）：std::fstream
// ● 字符串流：std::stringstream, std::istringstream, std::ostringstream


#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>


/*
实际应用示例
示例说明：读取一个文本文件，统计单词出现的次数，并将结果写入另一个文件。
*/

int text_analyzer(const std::string& input_file, const std::string& output_file) {
    std::ifstream ifs(input_file);
    if (!ifs.is_open()) {
        std::cerr << "Error: Failed to open input file: " << input_file << std::endl;
        return 1;
    }

    std::map<std::string, int> mp;

    std::string word;
    while (ifs >> word) {
        // 1. 转小写
        std::transform(word.begin(), word.end(), word.begin(), 
                    [](unsigned char c){ return std::tolower(c); });

        // 2. 将非字母字符替换为空格
        for (char& c : word) {
            if (!std::isalpha(static_cast<unsigned char>(c))) {
                c = ' ';
            }
        }
        
        // ifs >> word 可能会读取到字符串 "ai(artificial-intelligence)"。
        // 循环将括号和连字符替换为空格，结果变为 "ai artificial intelligence "。
        // mp[word]++ 会把这整个带有空格的字符串作为一个单词存入 map。

        // 3. 使用 stringstream 拆分可能被空格隔开的多个单词
        std::stringstream ss(word);
        std::string subWord;
        while (ss >> subWord) {
            mp[subWord]++;
        }
    }

    ifs.close();

    std::ofstream ofs(output_file, std::ios::trunc);
    if (!ofs.is_open()) {
        std::cerr << "Error: Failed to open output file: " << output_file << std::endl;
        return 1;
    }

    for (const auto& pair : mp) {
        ofs << pair.first << ": " << pair.second << std::endl;
    }

    ofs.close();

    std::cout << "Text analysis completed. Output written to: " << output_file << std::endl;

    return 0;
}



int main() {
    std::string input_file = "input.txt";
    std::string output_file = "output.txt";
    return text_analyzer(input_file, output_file);
}