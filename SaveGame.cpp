#include <iostream>
#include "Board.h"
#include <fstream>
#include "SaveGame.h"

void ReadGame(const string &filename) 
{
    ifstream file;
    file.open(filename);
    if (!file.is_open()) {

    }
    file >> boardSize;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            file >> board[i][j];
        }
    }
    file.close();

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}


void SaveGame(const string &filename){

    ofstream file(filename);
    file << boardSize;
    file << "\n";

    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            file << board[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
}

