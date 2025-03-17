#include "Input.h"
#include <conio.h>
#include <iostream>

using namespace std;

char getMove(){
    char key;
    key = _getch();// Đọc phím từ người chơi
    if(key == 'w' || key == 'W') return 'w';
    if(key == 's' || key == 'S') return 's';
    if(key == 'a' || key == 'A') return 'a';
    if(key == 'd' || key == 'D') return 'd';

    return '\0'; // Nếu nhập phím không hợp lệ
}
