#include "input.h"
#include "UndoRedo.h"
#include "Board.h"
#include <conio.h>
#include <iostream>

using namespace std;

void showInstructions() 
{
    cout << "\n";
    cout << "   HOW TO PLAY \n";
    cout << "---------------------\n";
    cout << " W - Move Up\n";
    cout << " S - Move Down\n";
    cout << " A - Move Left\n";
    cout << " D - Move Right\n";
    cout << " Z - Undo\n";
    cout << " Y - Redo\n";
    cout << " Reach 2048 to win\n";
    cout << " Invalid keys will be ignored\n";
    cout << "---------------------\n";
    cout << "\n";
}

char getMove() {
    char key;
    while (true) 
    { 
        key = getch(); // Read keys from player
        key = tolower(key); // Convert to lowercase for ease of handling

        if (key == 'w' || key == 'a' || key == 's' || key == 'd') 
        {
            return key;
        } 
        else if (key == 'z') 
        {
            undoMove();
            printBoard();  
            showInstructions();
            continue;
        } 
        else if (key == 'y') 
        {
            redoMove();
            printBoard(); 
            showInstructions();
            continue;
        }
        else
        {
            cout << endl << "Invalid key! Please enter W, A, S, D, Z or Y" << endl;
        }
    }
}
