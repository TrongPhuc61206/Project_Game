#include "UserAuth.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>
#include <vector>

using namespace std;

// Constructor: Khởi tạo cây BST rỗng
UserAuth::UserAuth() : root(nullptr) {}

// Destructor: Giải phóng bộ nhớ khi đối tượng bị hủy
UserAuth::~UserAuth()
{
    deleteTree(root);
}

// Hàm đệ quy để xóa toàn bộ cây BST
void UserAuth::deleteTree(User *node)
{
    if (node)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Hàm băm mật khẩu đơn giản (XOR trên 32 byte đầu)
std::string hashPassword(const std::string &password)
{
    std::vector<unsigned char> hash(32, 0); // Mảng 32 byte khởi tạo với 0
    for (size_t i = 0; i < password.size(); ++i)
    {
        hash[i % 32] ^= password[i]; // XOR từng ký tự vào mảng hash
    }
    std::ostringstream oss;
    for (unsigned char c : hash)
    {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return oss.str(); // Trả về chuỗi băm dưới dạng hex
}

// Hàm chèn người dùng vào BST
void UserAuth::insert(User *&node, const std::string &username, const std::string &passwordHash)
{
    if (!node)
    {
        node = new User{username, passwordHash, nullptr, nullptr}; // Tạo nút mới nếu chưa tồn tại
        return;
    }
    if (username < node->username)
        insert(node->left, username, passwordHash); // Chèn vào nhánh trái nếu username nhỏ hơn
    else if (username > node->username)
        insert(node->right, username, passwordHash); // Chèn vào nhánh phải nếu username lớn hơn
}

// Đăng ký người dùng mới (băm mật khẩu trước khi lưu)
void UserAuth::registerUser(const std::string &username, const std::string &password)
{
    std::string passwordHash = hashPassword(password);
    insert(root, username, passwordHash);
}

// Tìm kiếm người dùng trong BST và kiểm tra mật khẩu
bool UserAuth::search(User *node, const std::string &username, const std::string &password)
{
    if (!node)
        return false; // Không tìm thấy người dùng
    if (node->username == username)
        return node->passwordHash == hashPassword(password); // So sánh mật khẩu băm
    return username < node->username ? search(node->left, username, password) : search(node->right, username, password);
}

// Đăng nhập: tìm kiếm username và kiểm tra mật khẩu
bool UserAuth::loginUser(const std::string &username, const std::string &password)
{
    return search(root, username, password);
}

// Lưu toàn bộ người dùng từ BST vào file "users.txt"
void UserAuth::saveUsersToFile()
{
    std::ofstream file("users.txt");
    if (!file)
        return;
    
    // Hàm lambda duyệt cây theo thứ tự trước và ghi vào file
    std::function<void(User *)> save = [&](User *node)
    {
        if (!node)
            return;
        file << node->username << " " << node->passwordHash << "\n"; // Ghi username và hash mật khẩu
        save(node->left);
        save(node->right);
    };
    save(root);
    file.close();
}

// Đọc dữ liệu từ file "users.txt" và tải vào BST
void UserAuth::loadUsersFromFile()
{
    std::ifstream file("users.txt");
    if (!file)
        return;
    std::string username, passwordHash;
    while (file >> username >> passwordHash)
    {
        insert(root, username, passwordHash); // Chèn từng người dùng vào BST
    }
    file.close();
}
