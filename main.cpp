#include <iostream>
#include "Board.h"
#include "Movement.h"
#include "input.h"

using namespace std;

int main() 
{
    cout << "Enter board size: ";
    int n;
    cin >> n;

    initBoard(n);

    while (canMove()) 
    {
        system("cls"); // Clear screen before redisplaying panel (Windows)
        printBoard();  // Show game board
        showInstructions(); // Show instructions just below the table

        char c;
        do 
        {
            c = getMove();
        } 
        while (c == '\0'); // Repeat if wrong character entered

        if (c == 'w') moveUp();
        if (c == 's') moveDown();
        if (c == 'a') moveLeft();
        if (c == 'd') moveRight();

        addRandom();
        addRandom();
    }

    cout << "Game Over!" << endl;
    return 0;
}

