#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <fstream>
#include <atomic>

// 日志级别
enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error,
    Fatal
};

// 获取当前时间
std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    char buffer[64];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now_time));
    return std::string(buffer);
}

// 辅助函数，将单个参数转换为字符串
template<typename T>
std::string to_string_helper(T&& arg) {
    std::ostringstream oss;
    oss << std::forward<T>(arg);
    return oss.str();
}

// 线程安全的日志队列
class LogQueue {
private:
    std::queue<std::string> queue_;
    std::mutex mutex_;
    std::condition_variable cond_var_;
    bool is_shutdown_ = false;

public:
    void push(const std::string& msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(msg);
        cond_var_.notify_one();
    }

    bool pop(std::string& msg) {
        std::unique_lock<std::mutex> lock(mutex_);
        while(queue_.empty() && !is_shutdown_) {
            cond_var_.wait(lock);
        }
        if(is_shutdown_ && queue_.empty()) {
            return false;
        }
        msg = queue_.front();
        queue_.pop();
        return true;
    }

    void shutdown() {
        std::lock_guard<std::mutex> lock(mutex_);
        is_shutdown_ = true;
        cond_var_.notify_all();
    }
};

// Logger 类
class Logger {
private:
    LogQueue log_queue_;
    std::thread logger_thread_;
    std::ofstream log_file_;
    std::atomic<bool> exit_flag_;

    //   根据日志文件大小进行日志文件的轮转，防止单个日志文件过大。
    void processQueue() {
        std::string msg;
        static std::mutex file_mutex_;

        while(log_queue_.pop(msg)) {
            std::lock_guard<std::mutex> lock(file_mutex_);      // 使用互斥锁保护文件操作
            // 检查日志文件大小是否超过10KB
            if (log_file_.is_open() && log_file_.tellp() > 10 * 1024) {
                log_file_.close();
                std::string new_file = "log/log-" + getCurrentTime() + ".txt";
                log_file_.open(new_file, std::ios::out | std::ios::app);
            }

            if (log_file_.is_open()) {
                log_file_ << msg << std::endl;
            }
        }
    }

    // 使用模板折叠格式化消息, 支持{}占位符
    template<typename... Args>
    std::string formatMessage(const std::string& format, Args&&... args) {
        std::vector<std::string> arg_strings = {to_string_helper(std::forward<Args>(args))...};
        std::ostringstream oss;
        oss << "(" << getCurrentTime() << ") ";
        size_t arg_index = 0;
        size_t pos = 0;
        size_t placeholder = format.find("{}", pos);

        while(placeholder != std::string::npos) {
            oss << format.substr(pos, placeholder - pos);
            if(arg_index < arg_strings.size()) {
                oss << arg_strings[arg_index++];
            } else {
                oss << "{}";            // 没有足够的参数，保留 "{}"
            }
            pos = placeholder + 2;      // 跳过 "{}"
            placeholder = format.find("{}", pos);
        }

        oss << format.substr(pos);      // 添加剩余的字符串

        while(arg_index < arg_strings.size()) {     // 如果还有剩余的参数，按原方式拼接
            oss << arg_strings[arg_index++];
        }

        return oss.str();
    }

public:
    Logger(const std::string& filename) : log_file_(filename, std::ios::out | std::ios::app) {
        if (!log_file_.is_open()) {
            throw std::runtime_error("Failed to open log file: " + filename);
        }
        logger_thread_ = std::thread(&Logger::processQueue, this);
    }

    ~Logger() {
        log_queue_.shutdown();               // 关闭队列，通知线程结束

        if (logger_thread_.joinable()) {     // 等待线程结束
            logger_thread_.join();
        }

        if (log_file_.is_open()) {          // 关闭日志文件
            log_file_.close();
        }
    }

    // 日志接口：支持带格式字符串的日志, 支持{}占位符, 并添加当前时间, 日志级别
    template<typename... Args>
    void log(LogLevel level, const std::string& format, Args&&... args) {
        std::string level_str;
        switch(level) {
            case LogLevel::Debug:
                level_str = "[DEBUG]";
                break;
            case LogLevel::Info:
                level_str = "[INFO]";
                break;
            case LogLevel::Warning:
                level_str = "[WARNING]";
                break;
            case LogLevel::Error:
                level_str = "[ERROR]";
                break;
            case LogLevel::Fatal:
                level_str = "[FATAL]";
                break;
        }

        std::string msg = formatMessage(format, std::forward<Args>(args)...);
        log_queue_.push(level_str + " " + msg);
    }
};