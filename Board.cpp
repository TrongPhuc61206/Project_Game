#include "Board.h"
#include <ctime>
#include <iostream>
#include <cstdlib>


int boardSize;
int board[10][10];


// Initialize 2048 board
void initBoard(int newsize)
{
    boardSize = newsize;
    srand(time(0));
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j] = 0;
        }
    }

    // Add 2 random number cells to the table
    addRandom();
    addRandom();
}

// Show game board
void printBoard() {
    system("cls"); // Clear screen 
    cout << "+";
    for (int i = 0; i < boardSize; i++) cout << "------+"; // Top horizontal border
    cout << endl;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            cout << "|";
            if (board[i][j] == 0)
                cout << "      "; // Blank cell
            else
                cout << " " << board[i][j] << string(5 - to_string(board[i][j]).length(), ' ');
        }
        cout << "|" << endl;

        cout << "+";
        for (int j = 0; j < boardSize; j++) cout << "------+"; // Bottom border
        cout << endl;
    }
}

// Add random number box
void addRandom()
{
    int emptyCells[100][2];
    int count = 0;

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board[i][j] == 0)
            {
                emptyCells[count][0] = i;
                emptyCells[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0)
    {
        int n = rand() % count;
        board[emptyCells[n][0]][emptyCells[n][1]] = (rand() % 10 == 0) ? 4 : 2;
    }
}

int showBoardSizeSelectionScreen()
{
    sf::RenderWindow window(sf::VideoMode(400, 300), "Select the size of the board", sf::Style::Close);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Không thể load font!\n";
        return -1;
    }

    // Load background image
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("images/background2.png"))
    {
        std::cerr << "Không thể load ảnh nền!\n";
        return -1;
    }
    sf::Sprite background(bgTexture);
    background.setScale(
        window.getSize().x / static_cast<float>(bgTexture.getSize().x),
        window.getSize().y / static_cast<float>(bgTexture.getSize().y));

    // Title
    sf::Text title("Select the size of the board", font, 24);
    title.setFillColor(sf::Color::Black);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setPosition((400 - titleBounds.width) / 2, 30); // Canh giữa

    // Kích thước nút
    int buttonWidth = 120, buttonHeight = 40;
    int totalWidth = 40 + 10 + buttonWidth + 10 + 40;
    int startX = (400 - totalWidth) / 2;
    int startY = 100;

    // Các lựa chọn kích thước
    int currentSize = 4;
    std::vector<std::string> sizes = {"4x4", "5x5", "6x6", "7x7", "8x8", "9x9", "10x10"};

    // Nút size
    sf::RectangleShape sizeButton(sf::Vector2f(buttonWidth, buttonHeight));
    sizeButton.setPosition(startX + 50, startY);
    sizeButton.setFillColor(sf::Color(255, 255, 153)); // Vàng nhạt
    sizeButton.setOutlineThickness(1);
    sizeButton.setOutlineColor(sf::Color::Black);

    sf::Text sizeLabel(sizes[currentSize - 4], font, 20);
    sizeLabel.setFillColor(sf::Color::Black);
    sizeLabel.setPosition(startX + 50 + 30, startY + 10);

    // Nút "<"
    sf::RectangleShape prevButton(sf::Vector2f(40, 40));
    prevButton.setPosition(startX, startY);
    prevButton.setFillColor(sf::Color(255, 255, 153));
    prevButton.setOutlineThickness(1);
    prevButton.setOutlineColor(sf::Color::Black);

    sf::Text prevButtonLabel("<", font, 22);
    prevButtonLabel.setFillColor(sf::Color::Black);
    prevButtonLabel.setPosition(startX + 10, startY + 5);

    // Nút ">"
    sf::RectangleShape nextButton(sf::Vector2f(40, 40));
    nextButton.setPosition(startX + 180, startY);
    nextButton.setFillColor(sf::Color(255, 255, 153));
    nextButton.setOutlineThickness(1);
    nextButton.setOutlineColor(sf::Color::Black);

    sf::Text nextButtonLabel(">", font, 22);
    nextButtonLabel.setFillColor(sf::Color::Black);
    nextButtonLabel.setPosition(startX + 190, startY + 5);

    // Nút OK
    sf::RectangleShape okButton(sf::Vector2f(100, 45));
    okButton.setPosition((400 - 100) / 2, startY + 60);
    okButton.setFillColor(sf::Color(0, 180, 100));
    okButton.setOutlineThickness(1);
    okButton.setOutlineColor(sf::Color::Black);

    sf::Text okText("OK", font, 22);
    okText.setFillColor(sf::Color::White);
    okText.setPosition((400 - 28) / 2, startY + 68); // Canh giữa nút OK

    // Vòng lặp sự kiện
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (prevButton.getGlobalBounds().contains(pos))
                {
                    if (currentSize > 4)
                    {
                        currentSize--;
                        sizeLabel.setString(sizes[currentSize - 4]);
                    }
                }

                if (nextButton.getGlobalBounds().contains(pos))
                {
                    if (currentSize < 10)
                    {
                        currentSize++;
                        sizeLabel.setString(sizes[currentSize - 4]);
                    }
                }

                if (okButton.getGlobalBounds().contains(pos))
                {
                    std::cout << "Selected size: " << sizes[currentSize - 4] << std::endl;
                    window.close();
                    return currentSize;
                }
            }
        }

        // Vẽ giao diện
        window.clear();
        window.draw(background); // Vẽ ảnh nền
        window.draw(title);
        window.draw(sizeButton);
        window.draw(sizeLabel);
        window.draw(prevButton);
        window.draw(prevButtonLabel);
        window.draw(nextButton);
        window.draw(nextButtonLabel);
        window.draw(okButton);
        window.draw(okText);
        window.display();
    }

    return -1;
}

