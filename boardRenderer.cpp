#include "boardRenderer.h"
#include "Board.h"
#include <iostream>

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

void drawTile(sf::RenderWindow& window, int value, float x, float y, float tileSize)
{
    sf::RectangleShape shape({ tileSize, tileSize });
    shape.setPosition({ x, y });
    shape.setFillColor(getTileColor(value));
    window.draw(shape);

    if (value > 0)
    {
        sf::Text text(std::to_string(value), font);
        text.setCharacterSize(static_cast<int>(tileSize / 3.5));
        text.setFillColor(sf::Color::Black);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        text.setPosition({ x + tileSize / 2, y + tileSize / 2 });

        window.draw(text);
    }
}

void drawBoard(sf::RenderWindow& window,
    float startX, float startY, float tileSize, float spacing,
    sf::Font& font)
{
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            float posX = startX + j * (tileSize + spacing);
            float posY = startY + i * (tileSize + spacing);

            // Vẽ nền ô số
            drawTile(window, board[i][j], posX, posY, tileSize);

            // Nếu ô có giá trị, thì vẽ số lên
            if (board[i][j] != 0)
            {
                sf::Text numberText;
                numberText.setFont(font);
                numberText.setString(std::to_string(board[i][j]));
                numberText.setCharacterSize(static_cast<unsigned int>(tileSize / 3));
                numberText.setFillColor(sf::Color::Black);

                // Căn giữa số trong ô
                sf::FloatRect textRect = numberText.getLocalBounds();
                numberText.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
                numberText.setPosition(posX + tileSize / 2, posY + tileSize / 2);

                window.draw(numberText);
            }
        }
    }
}


// Cập nhật hàm centerWindow để giữ cửa sổ luôn ở giữa màn hình
void centerWindow(sf::RenderWindow& window)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u windowSize = window.getSize();
    int posX = static_cast<int>((desktop.width - windowSize.x) / 2);
    int posY = static_cast<int>((desktop.height - windowSize.y) / 2);
    window.setPosition(sf::Vector2i(posX, posY));
}

