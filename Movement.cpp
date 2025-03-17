#include "Movement.h"
#include <iostream>
#include "Board.h"

using namespace std;

void moveLeft(){
    for(int i = 0; i < size; i++){
        int tmp[size] = {0}; // Mảng tạm để xử lí trên hàng i
        int idx = 0;


        // Dồn các số khác 0 về bên trái
        for(int j = 0; j < size; j++){
            if(board[i][j] != 0){
                tmp[idx++] = board[i][j];
            }
        }

        // Gộp các số giống nhau
        for(int j = 0; j < idx; j++){
            if(tmp[j] == tmp[j + 1] && tmp[j] != 0){
                tmp[j] *= 2;
                tmp[j + 1] = 0;
            }
        }

        // Dồn lại 1 lần nữa (vì sau lần gộp đầu tiên sẽ xuất hiện những ô có giá trị 0)
        int newtemp[size] = {0};
        int index = 0;
        for(int j = 0; j < size; j++){
            if(tmp[j] != 0){
                newtemp[index++] = tmp[j];
            }
        }

        // Cập nhật lại giá trị của hàng i sau khi moveLeft
        for(int j = 0; j < size; j++){
            board[i][j] = newtemp[j];
        }
    }
}

void moveRight(){
    for(int i = 0; i < size; i++){
        int tmp[size] = {0}; // Mảng tạm để xử lí trên hàng i
        int idx = size - 1; // Bắt đầu từ bên phải

        // Dồn các số khác 0 về bên phải
        for(int j = size - 1; j >= 0; j--){
            if(board[i][j] != 0){
                tmp[idx--] = board[i][j];
            }
        }

        // Gộp các số giống nhau
        for(int j = size - 1; j > 0; j--){
            if(tmp[j] == tmp[j - 1] && tmp[j] != 0){
                tmp[j] *= 2;
                tmp[j - 1] = 0;
            }
        }

        // Dồn lại 1 lần nữa
        int newtemp[size] = {0};
        int index = size - 1;
        for(int j = size - 1; j >= 0; j--){
            if(tmp[j] != 0){
                newtemp[index--] = tmp[j];
            }
        }

        // Cập nhật lại giá trị của hàng i sau khi moveRight
        for(int j = 0; j < size; j++){
            board[i][j] = newtemp[j];
        }
    }
}

void moveUp(){
    for(int j = 0; j < size; j++){
        int tmp[size] = {0}; // Mảng tạm để xử lí trên cột j
        int idx = 0;

        // Dồn các số khác 0 lên trên
        for(int i = 0; i < size; i++){
            if(board[i][j] != 0){
                tmp[idx++] = board[i][j];
            }
        }

        // Gộp các số giống nhau
        for(int i = 0; i < idx; i++){
            if(tmp[i] == tmp[i + 1] && tmp[i] != 0){
                tmp[i] *= 2;
                tmp[i + 1] = 0;
            }
        }

        // Dồn lại 1 lần nữa
        int newtemp[size] = {0};
        int index = 0;
        for(int i = 0; i < size; i++){
            if(tmp[i] != 0){
                newtemp[index++] = tmp[i];
            }
        }

        // Cập nhật lại giá trị của cột j sau khi moveUp
        for(int i = 0; i < size; i++){
            board[i][j] = newtemp[i];
        }
    }
}

void moveDown(){
    for(int j = 0; j < size; j++){
        int tmp[size] = {0}; // Mảng tạm để xử lí trên cột j
        int idx = size - 1;

        // Dồn các số khác 0 xuống dưới
        for(int i = size - 1; i >= 0; i--){
            if(board[i][j] != 0){
                tmp[idx--] = board[i][j];
            }
        }

        // Gộp các số giống nhau
        for(int i = size - 1; i > 0; i--){
            if(tmp[i] == tmp[i - 1] && tmp[i] != 0){
                tmp[i] *= 2;
                tmp[i - 1] = 0;
            }
        }

        // Dồn lại 1 lần nữa
        int newtemp[size] = {0};
        int index = size - 1;
        for(int i = size - 1; i >= 0; i--){
            if(tmp[i] != 0){
                newtemp[index--] = tmp[i];
            }
        }

        // Cập nhật lại giá trị của cột j sau khi moveDown
        for(int i = 0; i < size; i++){
            board[i][j] = newtemp[i];
        }
    }
}

bool canMove(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(board[i][j] == 0) return true; // Kiểm tra còn ô trống không
            if(i + 1 < size && board[i][j] == board[i + 1][j]) return true; // Kiểm tra xem có thể moveLeft hay moveRight không
            if(j + 1 < size && board[i][j] == board[i][j + 1]) return true; // Kiểm tra xem có thể moveUp hay moveDown không
        }
    }
    return false;
}
#include <iostream>
