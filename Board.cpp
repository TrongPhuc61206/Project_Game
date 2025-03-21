#include "Board.h"
#include <ctime>
#include <iostream>
#include <cstdlib>

int size;
int board[10][10];

// Khởi tạo bảng chơi 2048
void initBoard(int newsize){
    srand(time(0));
    size = newsize;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            board[i][j] = 0;
        }
    }

    //Thêm 2 ô số ngẫu nhiên vào bảng
    addRandom();
    addRandom();
}

// Hiển thị bảng chơi
void printBoard() {
    system("cls"); // Xóa màn hình 
    cout << "+";
    for (int i = 0; i < size; i++) cout << "------+"; // Viền ngang trên
    cout << endl;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << "|";
            if (board[i][j] == 0)
                cout << "      "; // Ô trống
            else
                cout << " " << board[i][j] << string(5 - to_string(board[i][j]).length(), ' ');
        }
        cout << "|" << endl;

        cout << "+";
        for (int j = 0; j < size; j++) cout << "------+"; // Viền ngang dưới
        cout << endl;
    }
}

// Thêm ô số ngẫu nhiên
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
        board[emptyCells[n][0]][emptyCells[n][1]] = (rand() % 50 == 0) ? 4 : 2;
    }
}
