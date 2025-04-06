#include "LeaderBoard.h"
using namespace std;

player data(int score, const string& name) {
    player data;
    data.Score = score;
    data.name = name;
    return data;
}

Node* createNode(const player& data) {
    Node* newnode = new Node;
    newnode->key = data;
    newnode->left = newnode->right = nullptr;
    return newnode;
}

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

void PrintLeaderBoard(Node* root) {
    if (root == nullptr) return;
    PrintLeaderBoard(root->right);
    cout << root->key.name << " - " << root->key.Score << endl;
    PrintLeaderBoard(root->left);
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

Node* loadLeaderboardFromFile(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) return nullptr;

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

void freeTree(Node* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
