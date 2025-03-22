#include "input.h"
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
    cout << " Reach 2048 to win\n";
    cout << " Invalid keys will be ignored\n";
    cout << "---------------------\n";
    cout << "\n";
}

char getMove() {
    char key;
    while (true) 
    { 
        key = _getch(); // Đọc phím từ người chơi
        key = tolower(key); // Chuyển về chữ thường để dễ xử lý

        if (key == 'w' || key == 'a' || key == 's' || key == 'd') 
        {
            return key;
        } 
        else 
        {
            cout << endl << "Invalid key! Please enter W, A, S or D" << endl;
        }
    }
}
