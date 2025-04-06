#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

const int MAX_BOARD_SIZE = 10; // Kích thước bảng lớn nhất
const int MIN_BOARD_SIZE = 4; // Kích thước bảng nhỏ nhất

// Khởi tạo menu chính
sf::Font font;
sf::Text newGameText, resumeGameText, settingsText, backText, boardSizeText;

void initMenu()
{
    if (!font.openFromFile("arial.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    newGameText.setFont(font);
    newGameText.setString("New Game");
    newGameText.setCharacterSize(40);
    newGameText.setPosition(sf::Vector2f(200.f, 150.f));

    resumeGameText.setFont(font);
    resumeGameText.setString("Resume");
    resumeGameText.setCharacterSize(40);
    resumeGameText.setPosition(sf::Vector2f(250.f, 250.f));

    settingsText.setFont(font);
    settingsText.setString("Settings");
    settingsText.setCharacterSize(40);
    settingsText.setPosition(sf::Vector2f(250.f, 350.f));
}

// Vẽ menu chính
void drawMainMenu(sf::RenderWindow &window)
{
    window.draw(newGameText);
    window.draw(resumeGameText);
    window.draw(settingsText);
}

void handleMenuInput(sf::Event &event, sf::RenderWindow &window, bool &gameRunning, bool &inMenu,
                     bool &newGame, bool &resumeGame, bool &inSettings,
                     sf::Text &newGameText, sf::Text &resumeGameText, sf::Text &settingsText)
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (newGameText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                newGame = true;
                inMenu = false;
                gameRunning = true;
            }
            else if (resumeGameText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                resumeGame = true;
                inMenu = false;
                gameRunning = true;
            }
            else if (settingsText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                inSettings = true;
            }
        }
    }
}

// Khởi tạo trò chơi mới
void initGame(int &boardSize, std::vector<std::vector<int>> &board)
{
    board.resize(boardSize, std::vector<int>(boardSize, 0));
    srand(static_cast<unsigned int>(time(0)));
    generateTile(board, boardSize);
    generateTile(board, boardSize);
}

// Tạo một ô mới với giá trị ngẫu nhiên
void generateTile(std::vector<std::vector<int>> &board, int boardSize)
{
    int x = rand() % boardSize;
    int y = rand() % boardSize;
    while (board[x][y] != 0)
    {
        x = rand() % boardSize;
        y = rand() % boardSize;
    }
    board[x][y] = (rand() % 2 + 1) * 2;
}

// Vẽ bảng trò chơi
void drawBoard(sf::RenderWindow &window, const std::vector<std::vector<int>> &board, int boardSize)
{
    float tileSize = 600.0f / boardSize;
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(sf::Vector2f(j * tileSize, i * tileSize));
            if (board[i][j] == 0)
            {
                tile.setFillColor(sf::Color(204, 192, 179)); // Màu ô trống
            }
            else
            {
                tile.setFillColor(sf::Color(238, 228, 218)); // Màu ô có giá trị
            }
            window.draw(tile);
        }
    }
}

// Vẽ màn hình kết thúc trò chơi
void drawGameOver(sf::RenderWindow &window)
{

    sf::Text gameOverText(font, "Game Over", 50);
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(sf::Vector2f(200.f, 200.f));
    window.draw(gameOverText);
}

// Vẽ màn hình cài đặt
void drawSettingsMenu(sf::RenderWindow &window, int &boardSize)
{
    boardSizeText.setFont(font);
    boardSizeText.setString("Board Size: " + std::to_string(boardSize) + "x" + std::to_string(boardSize));
    boardSizeText.setCharacterSize(40);
    boardSizeText.setFillColor(sf::Color::White);
    boardSizeText.setPosition(sf::Vector2f(250.f, 150.f));

    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(40);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(sf::Vector2f(250.f, 250.f));

    window.draw(boardSizeText);
    window.draw(backText);
}

// Xử lý sự kiện cài đặt
void handleSettingsInput(sf::Event &event, sf::RenderWindow &window, int &boardSize, bool &inSettings)
{
    std::optional<sf::Event> event;
    while (event = window.pollEvent())
    {
        if (event && event->getIf<sf::Event::Closed>())
        {
            window.close();
        }
        if (event.value().type == sf::Event::MouseButtonPressed && event.value().mouseButton.button == sf::Mouse::Button::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            // Điều chỉnh kích thước bảng
            if (boardSizeText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                if (boardSize < MAX_BOARD_SIZE)
                {
                    boardSize++;
                }
                else
                {
                    boardSize = MIN_BOARD_SIZE;
                }
            }

            // Quay lại menu
            if (backText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                inSettings = false;
            }
        }
    }
}
 
