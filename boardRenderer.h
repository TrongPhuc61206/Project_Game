#pragma once
#include <SFML/Graphics.hpp>
#include <string>

bool loadFont(const std::string& fontPath);

void drawTile(sf::RenderWindow& window, int value, float x, float y);

void drawBoard(sf::RenderWindow& window, int boardSize, int board[10][10], float startX, float startY);

void centerWindow(sf::RenderWindow& window);
