#ifndef USER_AUTH_H
#define USER_AUTH_H

#include <string>

// Cấu trúc dữ liệu cho User
struct User
{
    std::string username;
    std::string passwordHash;
    User *left;
    User *right;
};

// Các hàm xử lý đăng nhập / đăng ký
void registerUser(const std::string &username, const std::string &password);
bool loginUser(const std::string &username, const std::string &password);
void saveUsersToFile();
void loadUsersFromFile();

#endif // USER_AUTH_H
