#include "Board.h"
#include <ctime>
#include <iostream>
#include <cstdlib>


int boardSize;
int board[10][10];


// Initialize 2048 board
void initBoard(int newsize){
    srand(time(0));
    boardSize = newsize;

    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            board[i][j] = 0;
        }
    }

    // Add 2 random number cells to the table
    addRandom();
    addRandom();
}

// Show game board
void printBoard() {
    system("cls"); // Clear screen 
    cout << "+";
    for (int i = 0; i < boardSize; i++) cout << "------+"; // Top horizontal border
    cout << endl;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            cout << "|";
            if (board[i][j] == 0)
                cout << "      "; // Blank cell
            else
                cout << " " << board[i][j] << string(5 - to_string(board[i][j]).length(), ' ');
        }
        cout << "|" << endl;

        cout << "+";
        for (int j = 0; j < boardSize; j++) cout << "------+"; // Bottom border
        cout << endl;
    }
}

// Add random number box
void addRandom(){
    int emptyCells[100][2];
    int count = 0;
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            if(board[i][j] == 0){
                emptyCells[count][0] = i;
                emptyCells[count][1] = j;
                count++;
            }
        }
    }
    if(count > 0){
        int n = rand() % count;
        board[emptyCells[n][0]][emptyCells[n][1]] = (rand() % 50 == 0) ? 4 : 2;
    }
}
