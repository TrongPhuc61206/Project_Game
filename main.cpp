#include <iostream>
#include "Board.h"
#include "Movement.h"
#include "input.h"
#include "SaveGame.h"
#include <fstream>
#include "UserAuth.h"
#include "Leaderboard.h"

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
        cout << "Invalid choice. Enter 1 or 2: ";
    }
    cin.ignore();

    string username, password;
    bool authenticated = false;

    if (choice == 1)
    {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        registerUser(username, password);
        saveUsersToFile();
        authenticated = true;
    }
    else if (choice == 2)
    {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        authenticated = loginUser(username, password);
    }


    if (!authenticated)
    {
        cout << "Authentication failed. Exiting...\n";
        return 1;
    }
    cout << "Enter board size: ";
    int n;
    cin >> n;
    string filename = username + ".txt";
    ifstream file(filename);
    if (file.good() && file.peek() != ifstream::traits_type::eof()) { 
        ReadGame(filename); // Đọc game cũ
    } else {
        initBoard(n); // Tạo game mới
    }
    file.close();

    while (canMove()) 
    {
        ReadGame(filename);
        cout << "Score: " << score;
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
        SaveGame(filename);
    }
    Node* root = nullptr;
    player P  = data(score, username);
    insertNode(root, P);
    ofstream leaderboardfile("leaderboard.dat", ios::binary | ios::out); 
    saveLeaderboard(root, leaderboardfile);
    leaderboardfile.close();
    loadLeaderboardFromFile("leaderboard.dat");
    ClearFile(filename);
    cout << "Game Over!" << endl;
    cout << "Leader Board:" << endl;
    PrintLeaderBoard(root);
    score = 0;
    return 0;
}

