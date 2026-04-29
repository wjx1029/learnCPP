#pragma once
#include <string>



struct User {
    size_t id;
    std::string username;
    size_t passwordHash;

    User() = default;
    User(size_t id, const std::string& username) : id(id), username(username) {}
};

