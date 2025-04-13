#include "boardRenderer.h"
#include <iostream>

sf::Font font;

bool loadFont(const std::string &fontPath)
{
    if (!font.loadFromFile(fontPath))
    {
        std::cerr << "Error loading font!" << std::endl;
        return false;
    }
    return true;
}

sf::Color getTileColor(int value)
{
    switch (value)
    {
    case 2:
        return sf::Color(238, 228, 218);
    case 4:
        return sf::Color(237, 224, 200);
    case 8:
        return sf::Color(242, 177, 121);
    case 16:
        return sf::Color(245, 149, 99);
    case 32:
        return sf::Color(246, 124, 95);
    case 64:
        return sf::Color(246, 94, 59);
    case 128:
        return sf::Color(237, 207, 114);
    case 256:
        return sf::Color(237, 204, 97);
    case 512:
        return sf::Color(237, 200, 80);
    case 1024:
        return sf::Color(237, 197, 63);
    case 2048:
        return sf::Color(237, 194, 46);
    default:
        return sf::Color(60, 58, 50);
    }
}

void drawTile(sf::RenderWindow &window, int value, float x, float y)
{
    sf::RectangleShape shape({100.f, 100.f});
    shape.setPosition({x, y});
    shape.setFillColor(getTileColor(value));
    window.draw(shape);

    if (value > 0)
    {
        sf::Text text(std::to_string(value), font, 30);
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        text.setPosition({x + 50, y + 50});

        window.draw(text);
    }
}

void drawBoard(sf::RenderWindow &window, int boardSize, int board[10][10], float startX, float startY)
{
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            float x = startX + j * 110.f;
            float y = startY + i * 110.f;
            drawTile(window, board[i][j], x, y);
        }
    }
}

void centerWindow(sf::RenderWindow &window)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u windowSize = window.getSize();
    int posX = static_cast<int>((desktop.width - windowSize.x) / 2);
    int posY = static_cast<int>((desktop.height - windowSize.y) / 2);
    window.setPosition(sf::Vector2i(posX, posY));
}
