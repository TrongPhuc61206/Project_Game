#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace std;
using namespace sf;
// Constants
const int MAX_BOARD_SIZE = 10;
const int MIN_BOARD_SIZE = 4;

// Global Variables
extern Font font;
extern sf::Text newGameText;
extern sf::Text resumeGameText;
extern sf::Text leaderboardText;
extern sf::Text settingsText;
extern sf::Text backText;
extern sf::Text boardSizeText;

// Function Declarations
void initGame(int &newsize);
void drawBoard(RenderWindow &window);
void drawGameOver(RenderWindow& window);

void initMenu();
void drawMainMenu(RenderWindow& window);
void handleMenuInput(Event& event, RenderWindow& window, bool& gameRunning, bool& inMenu,
                     bool& newGame, bool& resumeGame, bool& inSettings, bool& inLeaderboard);

void drawSettingsMenu(RenderWindow& window, int& boardSize);
void handleSettingsInput(sf::Event& event, RenderWindow& window, int& boardSize, bool& inSettings);

void drawLeaderboard(RenderWindow& window);
void handleLeaderboardInput(RenderWindow& window, bool& inLeaderboard);

