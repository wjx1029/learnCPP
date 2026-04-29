#pragma once
#include "User.h"
#include <map>

class AuthService {
private:
    std::map<std::string, User> users;                  // username -> User
    const std::string userPath = "../user/users.csv";

public:
    AuthService();

    bool registerUser(const std::string& username, const std::string& password);
    int loginUser(const std::string& username, const std::string& password);
    void saveUsers();   // 将用户信息保存到 users.csv
    void loadUsers();   // 程序启动时读取用户库

};
