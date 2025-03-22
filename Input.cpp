#include "input.h"
#include <conio.h>
#include <iostream>

using namespace std;

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
