#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include "TaskManager.h"
#include "Command.h"
#include "AuthService.h"

int main() {

    // 初始化认证服务
    AuthService authService;
    int loggedInUserId = -1;

    while(true) {
        // 1. 登录/注册环节
        std::cout << "1. Login  2. Register  0. Exit\n";
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            // 退出
            std::cout << "退出任务管理系统." << std::endl;
            return 0;
        }

        std::string username, password;
        std::cout << "请输入用户名: ";
        std::cin >> username;
        std::cout << "请输入密码: ";
        std::cin >> password;
        if (choice == 1) {
            // 登录
            loggedInUserId = authService.loginUser(username, password);
            if (loggedInUserId == -1) {
                std::cout << "登录失败." << std::endl;
            } else {
                std::cout << "登录成功." << std::endl;
            }
        } else if (choice == 2) {
            // 注册
            if (!authService.registerUser(username, password)) {
                std::cout << "注册失败." << std::endl;
            } else {
                std::cout << "注册成功." << std::endl;
            }
        } else {
            std::cout << "无效选择." << std::endl;
        }

        if (loggedInUserId != -1) {
            // 初始化任务管理器
            TaskManager taskManager(loggedInUserId);

            // 创建命令对象
            AddCommand addCmd(taskManager);
            DeleteCommand deleteCmd(taskManager);
            ListCommand listCmd(taskManager);
            UpdateCommand updateCmd(taskManager);
            // SaveCommand saveCmd(taskManager);
            // LoadCommand loadCmd(taskManager);
            
            // 命令映射
            std::unordered_map<std::string, std::unique_ptr<CommandBase>> commands;
            commands["add"] = std::make_unique<AddCommand>(taskManager);
            commands["delete"] = std::make_unique<DeleteCommand>(taskManager);
            commands["list"] = std::make_unique<ListCommand>(taskManager);
            commands["update"] = std::make_unique<UpdateCommand>(taskManager);
            // commands["save"] = std::make_unique<SaveCommand>(taskManager);
            // commands["load"] = std::make_unique<LoadCommand>(taskManager);

            std::cout << "欢迎使用任务管理系统." << std::endl;
            std::cout << "可用命令: add, delete, list, update, exit" << std::endl;

            std::string input;
            while(true) {
                std::cout << "\n>> ";
                std::getline(std::cin, input);
                if (input.empty()) {
                    continue;
                }

                // 分离命令和参数
                size_t pos = input.find(' ');
                std::string cmd = input.substr(0, pos);
                std::string args;
                if (pos != std::string::npos) {
                    args = input.substr(pos + 1);
                }

                // 处理帮助命令
                if (cmd == "help") {
                    std::cout << "可用命令:" << std::endl;
                    std::cout << "add <描述>,<优先级>,<截止日期> - 添加新任务." << std::endl;
                    std::cout << "delete <ID> - 删除任务." << std::endl;
                    std::cout << "list <排序选项> - 列出任务. 排序选项: 0-按ID, 1-按优先级, 2-按截止日期." << std::endl;
                    std::cout << "update <ID>,<描述>,<优先级>,<截止日期> - 更新任务." << std::endl;
                    // std::cout << "save - 保存任务." << std::endl;
                    // std::cout << "load - 加载任务." << std::endl;
                    continue;
                }

                // 处理退出命令
                if (cmd == "exit") {
                    std::cout << "谢谢使用! 再见." << std::endl;
                    break;
                }
                
                // 执行命令
                if (commands.find(cmd) != commands.end()) {
                    commands[cmd]->execute(args);
                } else {
                    std::cout << "未知命令. 请输入帮助获取可用命令." << std::endl;
                }
            }
        }

    }
    return 0;
}