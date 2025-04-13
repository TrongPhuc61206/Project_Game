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

//int boardSize;
//int board[10][10];

// ... (giữ nguyên các include và khai báo ở trên)

int main()
{
    std::string usernamelogin;
    sf::RenderWindow window(sf::VideoMode(600, 800), "2048 Game");

    if (!showLoginOrRegisterScreen(usernamelogin)) {
        std::cout << "Login failed or window closed.\n";
        return 0;
    }

    int boardSize;
    int board[10][10];

    boardSize = showBoardSizeSelectionScreen();
    if (boardSize == -1) {
        std::cout << "Invalid board size selected.\n";
        return 0;
    }

    std::cout << "Board size selected: " << boardSize << "x" << boardSize << std::endl;

    initBoard(boardSize);

    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cout << "Failed to load font!\n";
        return 0;
    }

    bool showMenu = true;
    int score = 0;

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);

        if (showMenu)
        {
            showMainMenu(window);
        }
        else
        {
            // Vẽ bảng game
            float spacing = 10.f;
            float topMargin = 120.f;
            float bottomMargin = 100.f;

            float availableWidth = window.getSize().x;
            float availableHeight = window.getSize().y - topMargin - bottomMargin;

            float maxTileSizeX = (availableWidth - (boardSize - 1) * spacing) / boardSize;
            float maxTileSizeY = (availableHeight - (boardSize - 1) * spacing) / boardSize;

            float tileSize = std::min(maxTileSizeX, maxTileSizeY);

            float boardPixelSize = boardSize * tileSize + (boardSize - 1) * spacing;
            float startX = (availableWidth - boardPixelSize) / 2.f;
            float startY = topMargin + (availableHeight - boardPixelSize) / 2.f;

            drawBoard(window, startX, startY, tileSize, spacing, font);

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

            // Thay thế xử lý phím với hàm getMove()
            if (!showMenu)
            {

                if (event.key.code == sf::Keyboard::W) {
                    moveUp();  // Di chuyển lên và cập nhật bảng
                }
                else if (event.key.code == sf::Keyboard::S) {
                    moveDown();  // Di chuyển xuống và cập nhật bảng
                }
                else if (event.key.code == sf::Keyboard::A) {
                    moveLeft();  // Di chuyển sang trái và cập nhật bảng
                }
                else if (event.key.code == sf::Keyboard::D) {
                    moveRight();  // Di chuyển sang phải và cập nhật bảng
                }
                addRandom();  // Thêm số ngẫu nhiên vào bảng sau mỗi lần di chuyển
            }
        }

        window.display();
    }

    return 0;
}


    
    
