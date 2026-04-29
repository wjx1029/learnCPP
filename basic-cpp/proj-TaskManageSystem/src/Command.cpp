#include "Command.h"
#include "TaskManager.h"
#include <cstddef>
#include <iostream>
#include <stdexcept>

// 添加任务命令
AddCommand::AddCommand(TaskManager& manager) : taskManager(manager) {}

void AddCommand::executeImpl(const std::string& args) {
    // 简单的参数解析：描述,优先级,截止日期
    size_t pos1 = args.find(',');
    size_t pos2 = args.find(',', pos1 + 1);

    if (pos1 == std::string::npos || pos2 == std::string::npos) {
        std::cout << "参数格式错误. 请使用: add <描述>,<优先级>,<截止日期>" << std::endl;
        return;
    }

    std::string description = args.substr(0, pos1);
    int priority = std::stoi(args.substr(pos1 + 1, pos2 - pos1 - 1));
    std::string deadline = args.substr(pos2 + 1);

    taskManager.addTask(description, priority, deadline);
    std::cout << "添加任务成功." << std::endl;
}


// 删除任务命令
DeleteCommand::DeleteCommand(TaskManager& manager) : taskManager(manager) {}

void DeleteCommand::executeImpl(const std::string& args) {
    try {
        size_t pos;
        int id = std::stoi(args, &pos);
        if (pos != args.length()) {
            std::cout << "参数格式错误. 请使用: delete <ID>" << std::endl;
            return;
        }
        taskManager.delTask(id);
        std::cout << "任务删除成功." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "参数格式错误. 请使用: delete <ID>" << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        std::cout << "ID超出范围. 请使用有效的任务ID. " << std::endl;
        return;
    }
}

// 列出任务命令
ListCommand::ListCommand(TaskManager& manager) : taskManager(manager) {}

void ListCommand::executeImpl(const std::string& args) {
    int sortOption = 0;
    if (!args.empty()) {
        sortOption = std::stoi(args);
    }
    taskManager.listTasks(sortOption);
}

// 更新任务命令
UpdateCommand::UpdateCommand(TaskManager& manager) : taskManager(manager) {}

void UpdateCommand::executeImpl(const std::string& args) {
    // 简单的参数解析：ID,描述,优先级,截止日期
    size_t pos1 = args.find(',');
    size_t pos2 = args.find(',', pos1 + 1);
    size_t pos3 = args.find(',', pos2 + 1);

    if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) {
        std::cout << "参数格式错误. 请使用: update <ID>,<描述>,<优先级>,<截止日期>" << std::endl;
        return;
    }

    int id = std::stoi(args.substr(0, pos1));
    std::string description = args.substr(pos1 + 1, pos2 - pos1 - 1);
    int priority = std::stoi(args.substr(pos2 + 1, pos3 - pos2 - 1));
    std::string deadline = args.substr(pos3 + 1);

    taskManager.updateTask(id, description, priority, deadline);
    std::cout << "任务更新成功." << std::endl;
}

// // 保存任务命令
// SaveCommand::SaveCommand(TaskManager& manager) : taskManager(manager) {}

// void SaveCommand::executeImpl(const std::string& args) {
//     if (!args.empty()) {
//         std::cout << "参数格式错误. 请使用: save" << std::endl;
//         return;
//     }
//     taskManager.saveTasks();
//     std::cout << "任务已保存." << std::endl;
// }

// // 加载任务命令
// LoadCommand::LoadCommand(TaskManager& manager) : taskManager(manager) {}

// void LoadCommand::executeImpl(const std::string& args) {
//     if (!args.empty()) {
//         std::cout << "参数格式错误. 请使用: load" << std::endl;
//         return;
//     }
//     taskManager.loadTasks();
//     std::cout << "任务已加载." << std::endl;
// }
