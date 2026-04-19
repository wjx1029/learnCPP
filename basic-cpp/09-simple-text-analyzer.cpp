/*
示例项目1：简易文本分析器
需求分析：

创建一个程序，接受用户输入的一段文本，并提供以下功能：

● 统计单词数量
● 统计每个单词出现的次数
● 查找指定单词的出现次数
● 输出最长的单词
*/

#include<iostream>
#include<string>
#include<map>
#include<sstream>
#include<algorithm>

using namespace std;

int main()
{
    string text, line;
    ostringstream oss;
    map<string, int> wordCount;

    cout << "请输入文本（直接按两次回车结束输入）: \n";
    while (getline(cin, line) && !line.empty()) 
    {
        oss << line << " ";
    }
    // 此时 cin 是完全正常的，不需要任何 clear() 操作

    text = oss.str();


    // 使用字符串流分割单词
    stringstream ss(text);
    string word;
    size_t totalWords = 0;
    string longestWord;

    while(ss >> word)
    {
        // 去除标点符号（简单处理）
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return ispunct(c);}), word.end());

        // 转为小写
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (!word.empty())
        {
            wordCount[word]++;
            totalWords++;
            if (word.size() > longestWord.size())   longestWord = word;
        }
    }


    
    cout << "\n统计结果: \n";
    cout << "单词总数: " << totalWords << endl;
    cout << "每个单词出现的次数: \n";
    for (auto it = wordCount.begin(); it != wordCount.end(); ++it)
    {
        cout << it->first << ": " << it->second << endl;
    } 

    cout << "最长的单词: " << longestWord << "\n\n";

    // 查找指定单词的出现次数
    std::string searchWord;
    std::cout << "\n请输入要查找的单词: ";
    std::cin >> searchWord;
    // 转为小写
    std::transform(searchWord.begin(), searchWord.end(), searchWord.begin(), ::tolower);
    auto it = wordCount.find(searchWord);
    if (it != wordCount.end()) {
        std::cout << "'" << searchWord << "' 出现了 " << it->second << " 次。" << std::endl;
    } else {
        std::cout << "'" << searchWord << "' 未在文本中找到。" << std::endl;
    }

    return 0;
}