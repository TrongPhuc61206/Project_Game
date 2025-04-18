#pragma once

#include <string>
#include <fstream>  
#include <iostream> 

using namespace std;

struct player {
    int Score;
    string name;
};

struct Node {
    player key;
    Node* left;
    Node* right;
};



player data(int score, const string& name);
Node* createNode(const player& data);
Node* insertNode(Node* root, const player& data);
void saveLeaderboard(Node* root, ofstream& outfile);
Node* loadLeaderboardFromFile(const char* filename);
void freeTree(Node* root);
void DrawLeaderBoard();
void Traversal(Node* root);
