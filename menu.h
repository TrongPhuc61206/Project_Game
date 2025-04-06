#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
extern const int MAX_BOARD_SIZE;
extern const int MIN_BOARD_SIZE;
// Các biến toàn cục dùng cho menu
extern sf::RectangleShape newGameButton;
extern sf::RectangleShape resumeGameButton;
extern sf::RectangleShape leaderboardButton;
extern sf::RectangleShape settingsButton;

extern sf::RectangleShape settingsBoardSizeButton;
extern sf::RectangleShape settingsBackButton;

extern sf::RectangleShape leaderboardTitle;
extern sf::RectangleShape leaderboardBackButton;

extern sf::Texture fontTexture;

// Các hàm khởi tạo và xử lý menu
bool loadFontTexture(const std::string& texturePath);
void createButton(sf::RectangleShape &button, sf::Vector2f position, sf::Vector2f size, sf::Color color);
void initMenu();
void drawMainMenu(sf::RenderWindow &window);
void handleMenuInput(sf::Event &event, sf::RenderWindow &window, bool &gameRunning, bool &inMenu,
                     bool &newGame, bool &resumeGame, bool &inSettings, bool &inLeaderboard);

void drawSettingsMenu(sf::RenderWindow &window, int &boardSize);
void handleSettingsInput(sf::Event &event, sf::RenderWindow &window, int &boardSize, bool &inSettings);

void drawLeaderboard(sf::RenderWindow &window);
void handleLeaderboardInput(sf::RenderWindow &window, bool &inLeaderboard);

#endif // MENU_H
