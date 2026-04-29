#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>

class Logger {
private:
    Logger();
    ~Logger();

    std::ofstream logFile;
    std::mutex mtx;

public:
    // 获取单例实例
    static Logger& getInstance();

    // 禁用复制构造函数和赋值运算符
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // 记录日志
    void log(const std::string& msg);
};


#endif