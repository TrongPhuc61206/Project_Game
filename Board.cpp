#include "Board.h"
#include <ctime>
#include <iostream>
#include <cstdlib>

int size;
int board[10][10];

void initBoard(int newsize){
    srand(time(0));
    size = newsize;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            board[i][j] = 0;
        }
    }
}

void printBoard(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(board[i][j] != 0){
                cout << board[i][j] << "\t";
            }
            else{
                cout << "\t";
            }
            cout << endl;
        }
    }
}

void addRandom(){
    int emptyCells[100][2];
    int count = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(board[i][j] == 0){
                emptyCells[count][0] = i;
                emptyCells[count][1] = j;
                count++;
            }
        }
    }
    if(count > 0){
        int n = rand() % count;
        board[emptyCells[n][0]][emptyCells[n][1]] = (rand() % 10 == 0) ? 4 : 2;
    }
}
