#include "boardRenderer.h"
#include "Board.h"
#include <iostream>

// With gpt chat support for SFML graphics

sf::Font font;
bool loadFont(const std::string& fontPath)
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
    case 2: return sf::Color(238, 228, 218);
    case 4: return sf::Color(237, 224, 200);
    case 8: return sf::Color(242, 177, 121);
    case 16: return sf::Color(245, 149, 99);
    case 32: return sf::Color(246, 124, 95);
    case 64: return sf::Color(246, 94, 59);
    case 128: return sf::Color(237, 207, 114);
    case 256: return sf::Color(237, 204, 97);
    case 512: return sf::Color(237, 200, 80);
    case 1024: return sf::Color(237, 197, 63);
    case 2048: return sf::Color(237, 194, 46);
    default: return sf::Color(60, 58, 50);
    }
}

void drawTile(sf::RenderWindow& window, int value, float x, float y, float size, sf::Font& font)
{
    sf::RectangleShape tile(sf::Vector2f(size, size));
    tile.setPosition(x, y);
    tile.setFillColor(getTileColor(value));
    window.draw(tile);

    if (value != 0) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(value));

        // Size chữ tùy vào số chữ số
        int length = text.getString().getSize();
        text.setCharacterSize(static_cast<unsigned int>(size / (length <= 2 ? 2.5 : (length <= 3 ? 3.0 : 3.5))));

        text.setFillColor(sf::Color::Black);

        // Canh giữa chữ
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
        text.setPosition(x + size / 2, y + size / 2);

        window.draw(text);
    }
}


void drawBoard(sf::RenderWindow& window, float startX, float startY, float tileSize, float spacing, sf::Font& font)
{
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            float posX = startX + j * (tileSize + spacing);
            float posY = startY + i * (tileSize + spacing);

             /*// Draw the tile background

            // If the tile has a value, draw the number on it
            if (board[i][j] != 0)
            {
                sf::Text numberText;
                numberText.setFont(font);
                numberText.setString(std::to_string(board[i][j]));
                numberText.setCharacterSize(static_cast<unsigned int>(tileSize / 3));
                numberText.setFillColor(sf::Color::Black);

                // Center the number in the tile
                sf::FloatRect textRect = numberText.getLocalBounds();
                numberText.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
                numberText.setPosition(posX + tileSize / 2, posY + tileSize / 2);

                window.draw(numberText);
                float posX = startX + j * (tileSize + spacing);
                float posY = startY + i * (tileSize + spacing);
                */
                drawTile(window, board[i][j], posX, posY, tileSize, font);  // <-- chỉ gọi 1 lần là đủ
                if (board[i][j] != 0)
                {
                    sf::Text numberText;
                    numberText.setFont(font);
                    numberText.setString(std::to_string(board[i][j]));
                    numberText.setCharacterSize(static_cast<unsigned int>(tileSize / 3));
                    numberText.setFillColor(sf::Color::Black);

                    // Căn giữa số
                    sf::FloatRect textRect = numberText.getLocalBounds();
                    numberText.setOrigin(textRect.left + textRect.width / 2.0f,
                        textRect.top + textRect.height / 2.0f);
                    numberText.setPosition(posX + tileSize / 2, posY + tileSize / 2);

                    window.draw(numberText);
                }
            
            
        }
    }
}


// Update the centerWindow function to keep the window always centered on the screen
void centerWindow(sf::RenderWindow& window)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u windowSize = window.getSize();
    int posX = static_cast<int>((desktop.width - windowSize.x) / 2);
    int posY = static_cast<int>((desktop.height - windowSize.y) / 2);
    window.setPosition(sf::Vector2i(posX, posY));
}
