#pragma once
#include <SFML/Graphics.hpp>

extern sf::Font font;

bool loadFont(const std::string& fontPath);
void drawBoard(sf::RenderWindow& window, float startX, float startY, float tileSize, float spacing, sf::Font& font);

void centerWindow(sf::RenderWindow& window);
