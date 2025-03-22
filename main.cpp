#include <iostream>
#include "Board.h"
#include "Movement.h"
#include "input.h"

using namespace std;

int main() 
{
    cout << "Nhap n: ";
    int n;
    cin >> n;

    initBoard(n);
    printBoard();

    while (canMove()) 
    {
        char c;
        do 
        {
            c = getMove();
        } 
        while (c == '\0'); // Lặp lại nếu nhập sai ký tự

        cout << c << endl;
        if (c == 'w') moveUp();
        if (c == 's') moveDown();
        if (c == 'a') moveLeft();
        if (c == 'd') moveRight();

        addRandom();
        printBoard();
    }

    cout << "Game Over!" << endl;
    return 0;
}
