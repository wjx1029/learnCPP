#include "TaskManager.h"
#include "Logger.h"
#include "Task.h"
#include <iostream>

bool TaskManager::compareByPriority(const Task& a, const Task& b) {
    return a.priority < b.priority;
}

bool TaskManager::compareByDeadline(const Task& a, const Task& b) {
    return a.deadline < b.deadline;
}

TaskManager::TaskManager(int userId) {
    currentUserId = userId;
    nextId = 1;
    loadTasks();
}


void TaskManager::addTask(const std::string& description, int priority, const std::string& deadline) {
    Task task;
    task.id = nextId++;
    task.description = description;
    task.priority = priority;
    task.deadline = deadline;
    tasks.push_back(task);
    Logger::getInstance().log("[ADD TASK]: " + task.toString() + " (User ID: " + std::to_string(currentUserId) + ")");
    saveTasks();
}

void TaskManager::delTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) {
        return task.id == id;
    } );

    if (it != tasks.end()) {
        Logger::getInstance().log("[DELETE TASK]: " + it->toString() + " (User ID: " + std::to_string(currentUserId) + ")");
        tasks.erase(it);
        saveTasks();
    } else {
        std::cout << "没有找到ID为 " << id << "的任务." << std::endl;
    }
}

void TaskManager::updateTask(int id, const std::string& description, int priority, const std::string& deadline) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) {
        return task.id == id;
    } );

    if (it != tasks.end()) {
        Logger::getInstance().log("[UPDATE TASK(from)]: " + it->toString() + " (User ID: " + std::to_string(currentUserId) + ")");
        it->description = description;
        it->priority = priority;
        it->deadline = deadline;
        Logger::getInstance().log("[UPDATE TASK(to)]: " + it->toString() + " (User ID: " + std::to_string(currentUserId) + ")");
        saveTasks();
    } else {
        std::cout << "没有找到ID为 " << id << "的任务." << std::endl;
    }
}

void TaskManager::listTasks(int sortOption) const {
    std::vector<Task> sortedTasks = tasks;
    switch(sortOption) {
        case 1:
            std::sort(sortedTasks.begin(), sortedTasks.end(), compareByPriority);
            break;
        case 2:
            std::sort(sortedTasks.begin(), sortedTasks.end(), compareByDeadline);
            break;
        default:
            break;
    }
    for (const auto& task : sortedTasks) {
        std::cout << task.toString() << std::endl;
    }
}

void TaskManager::loadTasks() {
    std::ifstream file(getFilePath());
    if (!file.is_open()) {
        Logger::getInstance().log("[LOAD TASKS]: Failed to open task file. (User ID: " + std::to_string(currentUserId) + ")");
        return;
    }
    std::string line;
    while(std::getline(file, line)) {
        Task task;
        std::istringstream iss(line);
        char delimiter;
        iss >> task.id >> delimiter;
        std::getline(iss, task.description, ',');
        iss >> task.priority >> delimiter;
        iss >> task.deadline;
        tasks.push_back(task);
        if (task.id >= nextId) nextId = task.id + 1;
    }
    file.close();
    Logger::getInstance().log("[LOAD TASKS]: Load all tasks. (User ID: " + std::to_string(currentUserId) + ")");
}

void TaskManager::saveTasks() const {
    std::ofstream file(getFilePath());
    if (!file.is_open()) {
        Logger::getInstance().log("[SAVE TASKS]: Failed to open task file. (User ID: " + std::to_string(currentUserId) + ")");
        return;
    } 
    for (const Task& task : tasks) {
        file << task.id << ","
             << task.description << ","
             << task.priority << ","
             << task.deadline << "\n";
    }
    file.close();
    Logger::getInstance().log("[SAVE TASKS]: Save all tasks. (User ID: " + std::to_string(currentUserId) + ")");
}

