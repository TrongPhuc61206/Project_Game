#include "menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h" // Assuming this defines boardSize and board

const int MAX_BOARD_SIZE = 10; // Kích thước bảng tối đa
const int MIN_BOARD_SIZE = 4; 

// Define the global font as a texture or sprite-based text
sf::Texture fontTexture;

// Define the global menu text objects as rectangles
sf::RectangleShape newGameButton;
sf::RectangleShape resumeGameButton;
sf::RectangleShape leaderboardButton;
sf::RectangleShape settingsButton;

sf::RectangleShape settingsBoardSizeButton;
sf::RectangleShape settingsBackButton;

sf::RectangleShape leaderboardTitle;
sf::RectangleShape leaderboardBackButton;

// Function to load a texture for text
bool loadFontTexture(const std::string& texturePath) {
    if (!fontTexture.loadFromFile(texturePath)) {
        std::cerr << "Error loading texture!" << std::endl;
        return false;
    }
    return true;
}

// Example function to create a button
void createButton(sf::RectangleShape &button, sf::Vector2f position, sf::Vector2f size, sf::Color color) {
    button.setPosition(position);
    button.setSize(size);
    button.setFillColor(color);
}

void initMenu() {
    // Load the font texture (you'll need to replace "font.png" with an actual texture file path)
    if (!loadFontTexture("button_texture.png")) {
        std::cerr << "Error loading button texture!" << std::endl;
        return;
    }

    // Initialize the buttons with positions, sizes, and colors
    createButton(newGameButton, sf::Vector2f(200.f, 150.f), sf::Vector2f(200.f, 50.f), sf::Color::Green);
    createButton(resumeGameButton, sf::Vector2f(250.f, 220.f), sf::Vector2f(200.f, 50.f), sf::Color::Blue);
    createButton(leaderboardButton, sf::Vector2f(200.f, 290.f), sf::Vector2f(200.f, 50.f), sf::Color::Yellow);
    createButton(settingsButton, sf::Vector2f(250.f, 360.f), sf::Vector2f(200.f, 50.f), sf::Color::Cyan);

    // Settings menu
    createButton(settingsBoardSizeButton, sf::Vector2f(180.f, 150.f), sf::Vector2f(200.f, 50.f), sf::Color::Magenta);
    createButton(settingsBackButton, sf::Vector2f(250.f, 250.f), sf::Vector2f(200.f, 50.f), sf::Color::Red);

    // Leaderboard menu
    createButton(leaderboardTitle, sf::Vector2f(150.f, 150.f), sf::Vector2f(300.f, 50.f), sf::Color::White);
    createButton(leaderboardBackButton, sf::Vector2f(250.f, 400.f), sf::Vector2f(200.f, 50.f), sf::Color::Red);
}

void drawMainMenu(sf::RenderWindow &window) {
    window.draw(newGameButton);
    window.draw(resumeGameButton);
    window.draw(leaderboardButton);
    window.draw(settingsButton);
}

void handleMenuInput(sf::Event &event, sf::RenderWindow &window, bool &gameRunning, bool &inMenu,
                     bool &newGame, bool &resumeGame, bool &inSettings, bool &inLeaderboard) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Check for interactions with menu buttons
        if (newGameButton.getGlobalBounds().contains(mouseF)) {
            newGame = true;
            inMenu = false;
            gameRunning = true;
        } else if (resumeGameButton.getGlobalBounds().contains(mouseF)) {
            resumeGame = true;
            inMenu = false;
            gameRunning = true;
        } else if (leaderboardButton.getGlobalBounds().contains(mouseF)) {
            inLeaderboard = true;
        } else if (settingsButton.getGlobalBounds().contains(mouseF)) {
            inSettings = true;
        }
    }
}

void drawSettingsMenu(sf::RenderWindow &window, int &boardSize) {
    window.draw(settingsBoardSizeButton);
    window.draw(settingsBackButton);
}

void handleSettingsInput(sf::Event &event, sf::RenderWindow &window, int &boardSize, bool &inSettings) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        if (settingsBoardSizeButton.getGlobalBounds().contains(mouseF)) {
            boardSize = (boardSize < MAX_BOARD_SIZE) ? boardSize + 1 : MIN_BOARD_SIZE;
        }

        if (settingsBackButton.getGlobalBounds().contains(mouseF)) {
            inSettings = false;
        }
    }
}

void drawLeaderboard(sf::RenderWindow &window) {
    window.draw(leaderboardTitle);
    window.draw(leaderboardBackButton);
}

void handleLeaderboardInput(sf::RenderWindow &window, bool &inLeaderboard) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        if (leaderboardBackButton.getGlobalBounds().contains(mouseF)) {
            inLeaderboard = false;
        }
    }
}
