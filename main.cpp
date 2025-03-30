#include <iostream>
#include <limits>
#include "Board.h"
#include "Movement.h"
#include "input.h"
#include "UndoRedo.h"
#include "UserAuth.h"

using namespace std;

int main()
{
    loadUsersFromFile(); // Tải danh sách người dùng từ file

    cout << "Welcome to 2048!\n";
    cout << "1. Register\n2. Login\nChoose an option: ";

    int choice;
    while (!(cin >> choice) || (choice != 1 && choice != 2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Enter 1 or 2: ";
    }
    cin.ignore();

    string username, password;
    bool authenticated = false;

    if (choice == 1)
    {
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);
        registerUser(username, password);
        saveUsersToFile();
        authenticated = true;
    }
    else if (choice == 2)
    {
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);
        authenticated = loginUser(username, password);
    }

    if (!authenticated)
    {
        cout << "Authentication failed. Exiting...\n";
        return 1;
    }

    int n;
    cout << "Enter board size: ";
    while (!(cin >> n) || n < 2)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid board size. Enter a number >= 2: ";
    }

    initBoard(n);

    while (canMove())
    {
        system("cls");
        printBoard();
        showInstructions();

        char move = getMove();
        if (move == 'w' || move == 's' || move == 'a' || move == 'd')
        {
            saveState();
            if (move == 'w') moveUp();
            if (move == 's') moveDown();
            if (move == 'a') moveLeft();
            if (move == 'd') moveRight();
            addRandom();
            addRandom();
        }
        else if (move == 'z')
        {
            undoMove();
        }
        else if (move == 'y')
        {
            redoMove();
        }
    }

    cout << "Game Over!\n";
    return 0;
}
