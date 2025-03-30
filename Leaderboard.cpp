#include "LeaderBoard.h"

player data(int score, const string &name){
    player data;
    data.Score = score;
    data.name = name;
    return data;
}

Node* createNode(const player &data){
    Node* newnode = new Node;
    newnode->key = data;
    newnode->left = newnode->right = nullptr;
    return newnode;
}

Node* insertNode(Node* root, const player &data){
    if(root == nullptr) return createNode(data);
    if(data.Score > root->key.Score){
        root->right = insertNode(root->right, data);
    }
    else if(data.Score < root->key.Score){
        root->left = insertNode(root->left, data);
    }
    return root;
}

void PrintLeaderBoard(Node* root){
    if(root == NULL) return;
    PrintLeaderBoard(root->left);
    cout << root->key.name << " - " << root->key.Score << endl;
    PrintLeaderBoard(root->right);
}

void saveLeaderboard(Node* root, ofstream &outfile) {
    if (!root) return;
    saveLeaderboard(root->left, outfile);
    outfile.write((char*)&root->key, sizeof(player));
    saveLeaderboard(root->right, outfile);
}

Node* loadLeaderboardFromFile(const char* filename) {
    ifstream file(filename, ios::binary);
    Node* root = nullptr;
    player p;
    while (file.read((char*)&p, sizeof(player))) {
        root = insertNode(root, p);
    }
    file.close();
    return root;
}

void find(Node* root, Node* &temp, const string &name){
    if(!root) return;
    if(temp) return;
    if(root->key.name == name){
        temp = root;
    }
    find(root->left, temp, name);
    find(root->right, temp, name);
}

Node* findPlayer(Node* root, const string &name){
    Node* temp = nullptr;
    find(root, temp, name);
    return temp;
} 
