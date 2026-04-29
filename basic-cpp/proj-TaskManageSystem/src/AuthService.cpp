#include "AuthService.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

AuthService::AuthService() {
    loadUsers();
}

bool AuthService::registerUser(const std::string& username, const std::string& password) {
    if (users.find(username) != users.end()) {
        std::cout << "用户名已存在." << std::endl;
        return false;
    }
    User newUser(users.size() + 1, username);
    newUser.passwordHash = std::hash<std::string>()(password);
    users[username] = newUser;
    saveUsers();
    return true;
}

int AuthService::loginUser(const std::string& username, const std::string& password) {
    if (users.find(username) == users.end()) {
        std::cout << "用户名不存在." << std::endl;
        return -1;
    }
    if (users[username].passwordHash != std::hash<std::string>()(password)) {
        std::cout << "密码错误." << std::endl;
        return -1;
    }
    return users[username].id;
}

void AuthService::saveUsers() {
    // 实现将用户信息保存到 users.csv 的逻辑
    std::ofstream outFile(userPath);
    for (const auto& user : users) {
        outFile << user.second.id << "," << user.second.username << "," << user.second.passwordHash << std::endl;
    }
    outFile.close();
}

void AuthService::loadUsers() {
    // 实现从 users.csv 加载用户数据的逻辑
    std::ifstream inFile(userPath);
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string idStr, username, passwordHashStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, username, ',');
        std::getline(ss, passwordHashStr, ',');
        users[username] = User(std::stoi(idStr), username);
        users[username].passwordHash = std::stoul(passwordHashStr);
    }
}
