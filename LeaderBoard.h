#pragma once
#include <iostream>
#include <iostream>
#include <fstream>

using namespace std;

struct player{
    int Score;
    string name;
};

struct Node{
    player key;
    Node* left;
    Node* right;
};

player data(int score, const string &name);
Node* createNode(const player &data);
Node* insertNode(Node* root, const player &data);
void PrintLeaderBoard(Node* root);
void saveLeaderboard(Node* root, ofstream &outfile);
Node* loadLeaderboardFromFile(const char* filename);
void find(Node* root, Node* &temp, const string &name);
Node* findPlayer(Node* root, const string &name);

