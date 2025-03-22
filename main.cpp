#include <iostream>
#include "Board.h"
#include "Movement.h"
#include "Input.h"

int main(){
    cout << "nhap n";
    int n;
    cin >> n;

    initBoard(n);
    printBoard();
    while(canMove()){
        char c = getMove();
        cout << c << endl;
        if(c == 'w') moveUp();
        if(c == 's') moveDown();
        if(c == 'a') moveLeft();
        if(c == 'd') moveRight();
        addRandom();
        printBoard();
    }

    return 0;
}
