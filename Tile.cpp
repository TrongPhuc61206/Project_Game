#include "tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional> // SFML 3.0 sử dụng std::optional cho event

sf::Font font; // Biến font toàn cục

// Hàm tải font
bool loadFont(const std::string& fontPath) 
{
    if (!font.openFromFile(fontPath)) {  // SFML 3.0: dùng openFromFile() thay vì loadFromFile()
        std::cerr << "Error loading font!" << std::endl;
        return false;
    }
    return true;
}

// Hàm lấy màu sắc dựa trên giá trị ô vuông
sf::Color getTileColor(int value) {
    switch (value) {
        case 2:    return sf::Color(238, 228, 218);
        case 4:    return sf::Color(237, 224, 200);
        case 8:    return sf::Color(242, 177, 121);
        case 16:   return sf::Color(245, 149, 99);
        case 32:   return sf::Color(246, 124, 95);
        case 64:   return sf::Color(246, 94, 59);
        case 128:  return sf::Color(237, 207, 114);
        case 256:  return sf::Color(237, 204, 97);
        case 512:  return sf::Color(237, 200, 80);
        case 1024: return sf::Color(237, 197, 63);
        case 2048: return sf::Color(237, 194, 46);
        default:   return sf::Color(60, 58, 50); // Màu cho số lớn hơn 2048
    }
}


// Hàm vẽ một ô vuông
void drawTile(sf::RenderWindow& window, int value, float x, float y) {
    sf::RectangleShape shape({100.f, 100.f}); // SFML 3.0: dùng {} thay vì ()
    shape.setPosition({x, y});
    shape.setFillColor(getTileColor(value));

    window.draw(shape);


    if (value > 0) {
        sf::Text text(font, std::to_string(value), 30); // SFML 3.0: khởi tạo text với font
        text.setFont(font);                        // Gán font
        text.setString(sf::String(std::to_string(value))); // Sử dụng sf::String
        text.setCharacterSize(30);                 // Kích thước chữ
        text.setFillColor(sf::Color::Black);  
        text.setFillColor(sf::Color::Black);

        // Căn giữa số trong ô vuông
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin({textBounds.size.x / 2, textBounds.size.y / 2}); // SFML 3.0: dùng size.x thay vì width
        text.setPosition({x + 50, y + 50});

        window.draw(shape);
        window.draw(text);
    } else {
        window.draw(shape);
    }
}

void centerWindow(sf::RenderWindow& window) {
    // Lấy kích thước màn hình
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Lấy kích thước cửa sổ hiện tại
    sf::Vector2u windowSize = window.getSize();

    // Tính toán vị trí để căn giữa
    int posX = static_cast<int>((desktop.size.x - windowSize.x) / 2);
    int posY = static_cast<int>((desktop.size.y - windowSize.y) / 2);

    // Đặt vị trí cửa sổ
    window.setPosition(sf::Vector2i(posX, posY));
}


 
