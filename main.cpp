#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Movement.h"
#include "input.h"
#include "SaveGame.h"
#include "UserAuth.h"
#include "Leaderboard.h"
#include "UndoRedo.h"
#include "tile.h"
#include "menu.h"

using namespace std;
int main()
{
string usernamelogin;
sf::RenderWindow window(sf::VideoMode(600, 700), "2048 Game");

if (!showLoginOrRegisterScreen(usernamelogin)) 
{
    std::cout << "Login failed or window closed.\n";
    return 0;  
}
int boardSize;
int board[10][10];

boardSize = showBoardSizeSelectionScreen();

if (boardSize != -1)
{
    std::cout << "Board size selected: " << boardSize << "x" << boardSize << std::endl;


    initBoard(boardSize);

    showMainMenu(window);

}
else
{
    std::cout << "Invalid board size selected.\n";
    return 0; 
}

