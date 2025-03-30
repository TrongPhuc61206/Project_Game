#include "UserAuth.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <functional>

using namespace std;

// Con trỏ gốc BST
User *root = nullptr;

// Hàm xóa toàn bộ cây
void deleteTree(User *node)
{
    if (node)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Hàm băm mật khẩu
string hashPassword(const string &password)
{
    vector<unsigned char> hash(32, 0);
    for (size_t i = 0; i < password.size(); ++i)
    {
        hash[i % 32] ^= password[i];
    }
    ostringstream oss;
    for (unsigned char c : hash)
    {
        oss << hex << setw(2) << setfill('0') << static_cast<int>(c);
    }
    return oss.str();
}

// Hàm chèn vào BST
void insert(User *&node, const string &username, const string &passwordHash)
{
    if (!node)
    {
        node = new User{username, passwordHash, nullptr, nullptr};
        return;
    }
    if (username < node->username)
        insert(node->left, username, passwordHash);
    else if (username > node->username)
        insert(node->right, username, passwordHash);
}

// Đăng ký tài khoản mới
void registerUser(const string &username, const string &password)
{
    string passwordHash = hashPassword(password);
    insert(root, username, passwordHash);
}

// Tìm kiếm người dùng trong BST
bool search(User *node, const string &username, const string &password)
{
    if (!node)
        return false;
    if (node->username == username)
        return node->passwordHash == hashPassword(password);
    return username < node->username ? search(node->left, username, password) : search(node->right, username, password);
}

// Đăng nhập
bool loginUser(const string &username, const string &password)
{
    return search(root, username, password);
}

// Lưu danh sách người dùng vào file
void saveUsersToFile()
{
    ofstream file("users.txt");
    if (!file)
        return;

    function<void(User *)> save = [&](User *node)
    {
        if (!node)
            return;
        file << node->username << " " << node->passwordHash << "\n";
        save(node->left);
        save(node->right);
    };
    save(root);
    file.close();
}

// Tải danh sách từ file
void loadUsersFromFile()
{
    ifstream file("users.txt");
    if (!file)
        return;

    string username, passwordHash;
    while (file >> username >> passwordHash)
    {
        insert(root, username, passwordHash);
    }
    file.close();
}
