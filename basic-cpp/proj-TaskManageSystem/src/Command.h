#ifndef COMMAND_H
#define COMMAND_H

#include "TaskManager.h"
#include <string>

class CommandBase {
public:
    virtual void execute(const std::string& args) = 0;
    virtual ~CommandBase() = default;
};

// CRTP 基类模板
template <typename Derived>
class Command : public CommandBase {
public:
    void execute(const std::string& args) {
        static_cast<Derived*>(this)->executeImpl(args);
    }
};

// 添加任务命令
class AddCommand : public Command<AddCommand> {
private:
    TaskManager& taskManager;
public:
    AddCommand(TaskManager& manager);
    void executeImpl(const std::string& args);
};

// 删除任务命令
class DeleteCommand : public Command<DeleteCommand> {
private:
    TaskManager& taskManager;
public:
    DeleteCommand(TaskManager& manager);
    void executeImpl(const std::string& args);
};

// 列出任务命令
class ListCommand : public Command<ListCommand> {
private:
    TaskManager& taskManager;
public:
    ListCommand(TaskManager& manager);
    void executeImpl(const std::string& args);

};

// 更新任务命令
class UpdateCommand : public Command<UpdateCommand> {
private:
    TaskManager& taskManager;
public:
    UpdateCommand(TaskManager& manager);
    void executeImpl(const std::string& args);
};

// // 保存任务命令
// class SaveCommand : public Command<SaveCommand> {
// private:
//     TaskManager& taskManager;
// public:
//     SaveCommand(TaskManager& manager);
//     void executeImpl(const std::string& args);
// };

// // 加载任务命令
// class LoadCommand : public Command<LoadCommand> {
// private:
//     TaskManager& taskManager;
// public:
//     LoadCommand(TaskManager& manager);
//     void executeImpl(const std::string& args);
// };

#endif