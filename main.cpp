#include <iostream>
#include "Board.h"
#include "Movement.h"
#include "input.h"

using namespace std;

int main() 
{
    cout << "Nhap kich thuoc bang: ";
    int n;
    cin >> n;

    initBoard(n);

    while (canMove()) 
    {
        system("cls"); // Xóa màn hình trước khi hiển thị lại bảng (Windows)
        printBoard();  // Hiển thị bảng game
        showInstructions(); // Hiển thị hướng dẫn ngay bên dưới bảng

        char c;
        do 
        {
            c = getMove();
        } 
        while (c == '\0'); // Lặp lại nếu nhập sai ký tự

        if (c == 'w') moveUp();
        if (c == 's') moveDown();
        if (c == 'a') moveLeft();
        if (c == 'd') moveRight();

        addRandom();
    }

    cout << "Game Over!" << endl;
    return 0;
}
