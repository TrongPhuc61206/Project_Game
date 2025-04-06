#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Constants
const int MAX_BOARD_SIZE = 10;
const int MIN_BOARD_SIZE = 4;

// Global Variables
extern sf::Font font;
extern sf::Text newGameText, resumeGameText, settingsText, leaderboardText, backText, boardSizeText;

// Function Declarations
void initGame(int& boardSize, std::vector<std::vector<int>>& board);
void drawBoard(sf::RenderWindow& window, const std::vector<std::vector<int>>& board, int boardSize);
void drawGameOver(sf::RenderWindow& window);

void initMenu();
void drawMainMenu(sf::RenderWindow& window);
void handleMenuInput(sf::Event& event, sf::RenderWindow& window, bool& gameRunning, bool& inMenu,
                     bool& newGame, bool& resumeGame, bool& inSettings, bool& inLeaderboard);

void drawSettingsMenu(sf::RenderWindow& window, int& boardSize);
void handleSettingsInput(sf::Event& event, sf::RenderWindow& window, int& boardSize, bool& inSettings);

void drawLeaderboard(sf::RenderWindow& window);
void handleLeaderboardInput(sf::RenderWindow& window, bool& inLeaderboard);

