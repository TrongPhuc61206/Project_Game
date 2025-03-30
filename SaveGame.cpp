#include <iostream>
#include "Board.h"
#include <fstream>
#include "SaveGame.h"

void ReadGame(const string &filename){
 
    ifstream file(filename);

    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            file >> board[i][j];
        }
    }
    file.close();
}

void SaveGame(const string &filename){

    ofstream file(filename);

    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            file << board[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
}

void ClearFile(const string &filename) {
    ofstream file(filename, ios::trunc);
    file.close();

}
