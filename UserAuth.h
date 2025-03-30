#pragma once
#include <string>

struct User 
{
    std::string username;
    std::string passwordHash;
    User* left;
    User* right;
};

class UserAuth 
{
public:
    UserAuth();
    ~UserAuth();
    void registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);
    void saveUsersToFile();
    void loadUsersFromFile();

private:
    User* root;
    void insert(User*& node, const std::string& username, const std::string& passwordHash);
    bool search(User* node, const std::string& username, const std::string& password);
    void deleteTree(User* node);
};
