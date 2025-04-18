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
#include "boardRenderer.h"
#include "menu.h"

using namespace std;

int main()
{
    std::string usernamelogin;
    sf::RenderWindow window(sf::VideoMode(600, 800), "2048 Game");

    if (!showLoginOrRegisterScreen(usernamelogin)) {
        std::cout << "Login failed or window closed " << endl;
        return 0;
    }
    boardSize = showBoardSizeSelectionScreen();
    if (boardSize == -1) {
        std::cout << "Invalid board size selected " << endl;
        return 0;
    }

    std::cout << "Board size selected: " << boardSize << "x" << boardSize << std::endl;

    initBoard(boardSize);

    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) 
    {
        std::cout << "Failed to load font! " << endl;
        return 0;
    }

    bool showMenu = true;
    int score = 0;

    while (window.isOpen())
    {
        window.clear(sf::Color::White);

        if (showMenu)
        {
            showMainMenu(window);
        }
        else
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        showMenu = false;
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                    {
                        showMenu = true;
                    }
                }
            }

            // Replace key handling with getMove() function
            if (!showMenu)
            {

                if (event.key.code == sf::Keyboard::W) {
                    moveUp();
                }
                else if (event.key.code == sf::Keyboard::S) {
                    moveDown();  // Move down and update the board
                }
                else if (event.key.code == sf::Keyboard::A) {
                    moveLeft();  // Move left and update the board
                }
                else if (event.key.code == sf::Keyboard::D) {
                    moveRight();  // Move right and update the board
                }
                addRandom();  // Add a random number to the board after each move
            }
        }

        window.display();
    }

    return 0;
}
