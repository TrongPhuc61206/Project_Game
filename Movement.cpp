#include "Movement.h"
#include <iostream>
#include "Board.h"
#include "Queue.h"

using namespace std;

void moveLeft(){
    for(int i = 0; i < size; i++){
        int frontIndex = 0, rearIndex = -1, sizequeue = 0;
        // Dồn các ô khác 0 về bên trái, nếu 2 ô bằng nhau thì gộp lại thành 1 ô
        for(int j = 0; j < size; j++){
            if(board[i][j] != 0){
                if(sizequeue == 0){
                    enqueue(board[i][j]);
                }
                else{
                    if(queue[rearIndex] == board[i][j]){
                        int tmp = board[i][j] * 2;
                        queue[rearIndex] = tmp;
                    }
                    else{
                        enqueue(board[i][j]);
                    }
                }
            }
        }


        // Cập nhật lại giá trị của hàng i sau khi moveLeft
        for(int j = frontIndex; j < size + frontIndex; j++){
            board[i][j] = queue[j];
        }
    }
}

void moveRight(){
    for(int i = 0; i < size; i++){
        int frontIndex = 0, rearIndex = -1, sizequeue = 0;
        // Dồn các ô khác 0 về bên phải, nếu 2 ô bằng nhau thì gộp lại thành 1 ô
        for(int j = size - 1; j >= 0; j--){
            if(board[i][j] != 0){
                if(sizequeue == 0){
                    enqueue(board[i][j]);
                }
                else{
                    if(queue[rearIndex] == board[i][j]){
                        int tmp = board[i][j] * 2;
                        queue[rearIndex] = tmp;
                    }
                    else{
                        enqueue(board[i][j]);
                    }
                }
            }
        }

        // Cập nhật lại giá trị của hàng i sau khi moveRight
        for(int j = 0; j < size; j++){
            board[i][size - 1 - j] = queue[frontIndex + j];
        }
    }
}

void moveUp(){
    for(int j = 0; j < size; j++){
        int frontIndex = 0, rearIndex = -1, sizequeue = 0;
        // Dồn các ô khác 0 lên trên, nếu 2 ô bằng nhau thì gộp lại thành 1 ô
        for(int i = 0; i < size; i++){
            if(board[i][j] != 0){
                if(sizequeue == 0){
                    enqueue(board[i][j]);
                }
                else{
                    if(queue[rearIndex] == board[i][j]){
                        int tmp = board[i][j] * 2;
                        queue[rearIndex] = tmp;
                    }
                    else{
                        enqueue(board[i][j]);
                    }
                }
            }
        }

        // Cập nhật lại giá trị của cột j sau khi moveUp
        for(int i = 0; i < size; i++){
            board[i][j] = queue[frontIndex + i];
        }
    }
}

void moveDown(){
    for(int j = 0; j < size; j++){
        int frontIndex = 0, rearIndex = -1, sizequeue = 0;
        // Dồn các ô khác 0 xuống dưới, nếu 2 ô bằng nhau thì gộp lại thành 1 ô
        for(int i = size - 1; i >= 0; i--){
            if(board[i][j] != 0){
                if(sizequeue == 0){
                    enqueue(board[i][j]);
                }
                else{
                    if(queue[rearIndex] == board[i][j]){
                        int tmp = board[i][j] * 2;
                        queue[rearIndex] = tmp;
                    }
                    else{
                        enqueue(board[i][j]);
                    }
                }
            }
        }

        // Cập nhật lại giá trị của cột j sau khi moveDown
        for(int i = 0; i < size; i++){
            board[size - 1 - i][j] = queue[frontIndex + i];
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
