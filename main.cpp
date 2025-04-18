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

    showMainMenu(window);

    /*sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) 
    {
        std::cout << "Failed to load font! " << endl;
        return 0;
    }*/

  
    //centerWindow(window);
    //window.setFramerateLimit(60); 

    //while (window.isOpen())
    //{
    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        if (event.type == sf::Event::Closed) {
    //            window.close();
    //        }

    //        if (event.type == sf::Event::KeyPressed) {
    //            if (event.key.code == sf::Keyboard::W) moveUp();
    //            if (event.key.code == sf::Keyboard::S) moveDown();
    //            if (event.key.code == sf::Keyboard::A) moveLeft();
    //            if (event.key.code == sf::Keyboard::D) moveRight();
    //            if (event.key.code == sf::Keyboard::Z) undoMove();
    //            if (event.key.code == sf::Keyboard::Y) redoMove();

    //            addRandom();
    //        }
    //    }

    //    window.clear(sf::Color(187, 173, 160));
    //    int tileSize = 100;
    //    int spacing = 10;
    //    int boardPixelSize = boardSize * tileSize + (boardSize - 1) * spacing;

    //    float startX = (window.getSize().x - boardPixelSize) / 2.f;
    //    float startY = (window.getSize().y - boardPixelSize) / 2.f;

    //    //drawBoard(window, startX, startY, tileSize, spacing, font); // <-- PHẢI gọi ở đây
    //    showMainMenu(window);


    //    // Vẽ bảng game ở đây

    //    window.display();

    //    if (!canMove()) {
    //        std::cout << "Game Over!\n";
    //        break;
    //    }
    

    return 0;
}
