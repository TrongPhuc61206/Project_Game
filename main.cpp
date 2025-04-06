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
    cout << "Welcome to 2048!\n";
    cout << "1. Register\n2. Login\nChoose an option: ";

    int choice;
    while (!(cin >> choice) || (choice != 1 && choice != 2))
    {
        cin.clear();
        cout << "Invalid choice. Enter 1 or 2: ";
    }

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

    string filename = username + ".txt";
    int boardSize; // Or load from file
    cin >> boardSize;
    int score = 0;

    const int tileSize = 100;
    const int padding = 20;
    int windowWidth = boardSize * tileSize + (boardSize - 1) * padding + 100;
    int windowHeight = boardSize * tileSize + (boardSize - 1) * padding + 100;
    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned>(windowWidth), static_cast<unsigned>(windowHeight)}),
        "2048 Game",
        sf::Style::Default);

    // Load font for tiles
    if (!loadFont("arial.ttf"))
    {
        return -1; // Font loading failed, exiting
    }

    centerWindow(window);
    window.setFramerateLimit(60);

    // Game state
    bool inMenu = true, gameRunning = false, newGame = false, resumeGame = false;
    bool inSettings = false, inLeaderboard = false;

    initMenu();

    while (window.isOpen())
    {
        optional<sf::Event> event;
        while (event = window.pollEvent())
        {
            if (event && event->getIf<sf::Event::Closed>())
                window.close();
            if (event)
            {
                if (inMenu)
                {
                    handleMenuInput(event.value(), window, gameRunning, inMenu, newGame, resumeGame, inSettings, inLeaderboard);
                }
                else if (inSettings)
                {
                    handleSettingsInput(event.value(), window, boardSize, inSettings);
                }
                else if (inLeaderboard)
                {
                    handleLeaderboardInput(window, inLeaderboard);
                }
                else if (gameRunning)
                {
                    if (event && event->getIf<sf::Event::KeyPressed>())
                    {
                        auto keyEvent = event->getIf<sf::Event::KeyPressed>();
                        if (keyEvent->scancode == sf::Keyboard::Scancode::W)
                            moveUp();
                        if (keyEvent->scancode == sf::Keyboard::Scancode::S)
                            moveDown();
                        if (keyEvent->scancode == sf::Keyboard::Scancode::A)
                            moveLeft();
                        if (keyEvent->scancode == sf::Keyboard::Scancode::D)
                            moveRight();
                        if (keyEvent->scancode == sf::Keyboard::Scancode::Z)
                            undoMove();
                        if (keyEvent->scancode == sf::Keyboard::Scancode::Y)
                            redoMove();

                        addRandom();
                        SaveGame(filename);
                    }
                }
            }
        }

        window.clear(sf::Color(187, 173, 160));
        const int gridWidth = boardSize * tileSize + (boardSize - 1) * padding;
        const int gridHeight = boardSize * tileSize + (boardSize - 1) * padding;
        const int startX = (windowWidth - gridWidth) / 2;
        const int startY = (windowHeight - gridHeight) / 2;

        for (int i = 0; i < boardSize; ++i)
        {
            for (int j = 0; j < boardSize; ++j)
            {
                float x = startX + j * (tileSize + padding);
                float y = startY + i * (tileSize + padding);
                drawTile(window, board[i][j], x, y);
            }
        }
        if (inMenu)
        {
            drawMainMenu(window);
        }
        else if (inSettings)
        {
            drawSettingsMenu(window, boardSize);
        }
        else if (inLeaderboard)
        {
            drawLeaderboard(window);
        }
        else if (gameRunning)
        {
            if (newGame)
            {
                initBoard(boardSize);
                newGame = false;
            }
            else if (resumeGame)
            {
                ifstream file(filename);
                if (file.good() && file.peek() != ifstream::traits_type::eof())
                {
                    ReadGame(filename);
                }
                else
                {
                    initBoard(boardSize);
                }
                file.close();
                resumeGame = false;
            }
        }

        window.display();
    }

    return 0;
}
