#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

 1. Xử lý logic trò chơi
void initGame(int &boardSize, std::vector<std::vector<int>> &board);
void drawBoard(sf::RenderWindow &window, const std::vector<std::vector<int>> &board, int boardSize);
void drawGameOver(sf::RenderWindow &window);

 2. Giao diện chính (Menu)
void initMenu();
void drawMainMenu(sf::RenderWindow &window);
void handleMenuInput(sf::Event &event, sf::RenderWindow &window, bool &gameRunning, bool &inMenu, 
                     bool &newGame, bool &resumeGame, bool &inSettings);

3. Màn hình Cài Đặt (Settings)
void drawSettingsMenu(sf::RenderWindow &window, int &boardSize);
void handleSettingsInput(sf::Event &event, sf::RenderWindow &window, int &boardSize, bool &inSettings);
