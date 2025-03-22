#include "Movement.h"
#include <iostream>
#include "Board.h"
#include "Queue.h"

using namespace std;

void moveLeft() {
    for (int i = 0; i < size; i++) {
        frontIndex = 0, rearIndex = -1, sizequeue = 0; // Reset queue cho mỗi hàng
        for (int j = 0; j < size; j++) {
            if (board[i][j] != 0) {
                if (sizequeue > 0 && queue[rearIndex] == board[i][j]) {
                    queue[rearIndex] *= 2; // Nếu 2 ô bằng nhau thì gộp ô
                } else {
                    enqueue(board[i][j]); // Thêm vào queue
                }
            }
        }
        // Cập nhật lại hàng i
        for (int j = 0; j < size; j++) {
            if (j < sizequeue) {
                board[i][j] = queue[frontIndex + j];
            } else {
                board[i][j] = 0; // Điền 0 vào ô trống
            }
        }
    }
}

void moveRight() {
    for (int i = 0; i < size; i++) {
        frontIndex = 0, rearIndex = -1, sizequeue = 0; // Reset queue cho mỗi hàng
        for (int j = size - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (sizequeue > 0 && queue[rearIndex] == board[i][j]) {
                    queue[rearIndex] *= 2; // Nếu 2 ô bằng nhau thì gộp ô
                } else {
                    enqueue(board[i][j]); // Thêm vào queue
                }
            }
        }
        // Cập nhật lại hàng i
        for (int j = 0; j < size; j++) {
            if (j < sizequeue) {
                board[i][size - 1 - j] = queue[frontIndex + j];
            } else {
                board[i][size - 1 - j] = 0; // Điền 0 vào ô trống
            }
        }
    }
}

void moveUp() {
    for (int j = 0; j < size; j++) {
        frontIndex = 0, rearIndex = -1, sizequeue = 0; // Reset queue cho mỗi cột
        for (int i = 0; i < size; i++) {
            if (board[i][j] != 0) {
                if (sizequeue > 0 && queue[rearIndex] == board[i][j]) {
                    queue[rearIndex] *= 2; // Nếu 2 ô bằng nhau thì gộp ô
                } else {
                    enqueue(board[i][j]); // Thêm vào queue
                }
            }
        }
        // Cập nhật lại cột j
        for (int i = 0; i < size; i++) {
            if (i < sizequeue) {
                board[i][j] = queue[frontIndex + i];
            } else {
                board[i][j] = 0; // Điền 0 vào ô trống
            }
        }
    }
}

void moveDown() {
    for (int j = 0; j < size; j++) {
        frontIndex = 0, rearIndex = -1, sizequeue = 0; // Reset queue cho mỗi cột
        for (int i = size - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (sizequeue > 0 && queue[rearIndex] == board[i][j]) {
                    queue[rearIndex] *= 2; // Nếu 2 ô bằng nhau thì gộp ô
                } else {
                    enqueue(board[i][j]); // Thêm vào queue
                }
            }
        }
        // Cập nhật lại cột j
        for (int i = 0; i < size; i++) {
            if (i < sizequeue) {
                board[size - 1 - i][j] = queue[frontIndex + i];
            } else {
                board[size - 1 - i][j] = 0; // Điền 0 vào ô trống
            }
        }
    }
}

bool canMove() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 2048) // Thắng cuộc
            {
                cout << "Chuc mung ban da chien thang. ";
                return false; // Trả về false để dừng game
            }
            if (board[i][j] == 0) return true; // Còn ô trống
            if (i + 1 < size && board[i][j] == board[i + 1][j]) return true; // Có thể di chuyển lên/xuống
            if (j + 1 < size && board[i][j] == board[i][j + 1]) return true; // Có thể di chuyển trái/phải
        }
    }
    return false; // Không thể di chuyển
}
