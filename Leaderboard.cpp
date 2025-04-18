#include "LeaderBoard.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

vector<player> leaderboard;

// Tạo một player mới
player data(int score, const string& name) {
    player data;
    data.Score = score;
    data.name = name;
    return data;
}

// Tạo một node mới
Node* createNode(const player& data) {
    Node* newnode = new Node;
    newnode->key = data;
    newnode->left = newnode->right = nullptr;
    return newnode;
}

// Chèn node vào cây theo điểm số giảm dần
Node* insertNode(Node* root, const player& data) {
    if (root == nullptr) return createNode(data);
    if (data.Score > root->key.Score) {
        root->right = insertNode(root->right, data);
    }
    else if (data.Score < root->key.Score) {
        root->left = insertNode(root->left, data);
    }
    return root;
}

// Duyệt cây để lưu vào vector leaderboard
void Traversal(Node* root) {
    if (root == nullptr) return;
    Traversal(root->right);
    leaderboard.push_back(root->key);
    Traversal(root->left);
}

void DrawLeaderBoard() {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Không thể tải font!" << endl;
        return;
    }

    sf::RenderWindow window(sf::VideoMode(600, 800), "Bảng xếp hạng");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(30, 30, 30)); // nền xám đậm

        for (size_t i = 0; i < leaderboard.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            text.setPosition(50, 50 + i * 40);
            text.setString(to_string(i + 1) + ". " + leaderboard[i].name + " - " + to_string(leaderboard[i].Score));
            window.draw(text);
        }

        window.display();
    }
}


void saveLeaderboard(Node* root, ofstream& outfile) {
    if (!root) return;
    saveLeaderboard(root->left, outfile);
    int nameLen = root->key.name.length();
    outfile.write((char*)&root->key.Score, sizeof(int));
    outfile.write((char*)&nameLen, sizeof(int));
    outfile.write(root->key.name.c_str(), nameLen);
    saveLeaderboard(root->right, outfile);
}

// Tải cây nhị phân từ file nhị phân
Node* loadLeaderboardFromFile(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Không thể mở file!" << endl;
        return nullptr;
    }

    Node* root = nullptr;
    while (true) {
        int score;
        int nameLen;

        if (!file.read((char*)&score, sizeof(int))) break;
        if (!file.read((char*)&nameLen, sizeof(int))) break;
        if (nameLen <= 0) continue;

        char* nameBuffer = new (nothrow) char[nameLen + 1];
        if (!nameBuffer) {
            file.close();
            return nullptr;
        }

        if (!file.read(nameBuffer, nameLen)) {
            delete[] nameBuffer;
            file.close();
            return nullptr;
        }
        nameBuffer[nameLen] = '\0';

        string name(nameBuffer);
        delete[] nameBuffer;

        root = insertNode(root, data(score, name));
    }

    file.close();
    return root;
}

// Giải phóng bộ nhớ cây nhị phân
void freeTree(Node* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
