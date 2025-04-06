#pragma once
using namespace std;


#include <SFML/Graphics.hpp>

// Hàm tải font
bool loadFont(const string& fontPath);

// Hàm lấy màu sắc ô vuông
sf::Color getTileColor(int value);

// Hàm vẽ ô vuông
void drawTile(sf::RenderWindow& window, int value, float x, float y);

// Hàm căn giữa cửa sổ
void centerWindow(sf::RenderWindow& window);

