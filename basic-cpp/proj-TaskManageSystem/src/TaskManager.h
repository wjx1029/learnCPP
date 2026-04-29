#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include <vector>
#include <string>
#include <algorithm>

class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId;
    int currentUserId;
    std::string getFilePath() const {
        // 生成任务文件路径
        // 格式：tasks_用户ID.csv
        return "../task/tasks_" + std::to_string(currentUserId) + ".csv";
    }

    // 辅助排序函数
    static bool compareByPriority(const Task& a, const Task& b);
    static bool compareByDeadline(const Task& a, const Task& b);

public:
    TaskManager(int userId);

    void addTask(const std::string& description, int priority, const std::string& deadline);
    void delTask(int taskId);
    void updateTask(int taskId, const std::string& description, int priority, const std::string& deadline);
    void listTasks(int sortOption = 0) const;   // 0-按ID, 1-按优先级, 2-按截止日期
    void loadTasks();
    void saveTasks() const;

};



#endif