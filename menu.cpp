#include <SFML/Graphics.hpp>
#include <iostream>
#include "boardRenderer.h"
#include "board.h"
#include "Movement.h"

// With gpt chat support for SFML graphics


void showMainMenu(sf::RenderWindow& mainwindow)
{
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Cannot load font!\n";
        return;
    }
    addRandom();
    addRandom();
    // Calculate the tileSize appropriate for the window size
    float spacing = 10.f;
    float maxBoardPixelWidth = 500.f; // Maximum size limit of the board
    float tileSize = (maxBoardPixelWidth - (boardSize - 1) * spacing) / boardSize;

    float boardWidth = boardSize * tileSize + (boardSize - 1) * spacing;
    float startX = (mainwindow.getSize().x - boardWidth) / 2.f;
    float startY = 120.f;

    // Score box
    sf::RectangleShape scoreBox(sf::Vector2f(150, 60));
    scoreBox.setFillColor(sf::Color(200, 200, 200));
    scoreBox.setPosition(30, 20);
    scoreBox.setOutlineThickness(2);
    scoreBox.setOutlineColor(sf::Color::Black);
    score = 9;
    string score1 = to_string(score);
    string Score = "Score\n " + score1;
    sf::Text scoreText(Score, font, 20);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(scoreBox.getPosition().x + 10, scoreBox.getPosition().y + 5);

    // Settings button
    sf::RectangleShape settingsBtn(sf::Vector2f(100, 40));
    settingsBtn.setFillColor(sf::Color(180, 180, 180));
    settingsBtn.setPosition(mainwindow.getSize().x - 130, 30);
    settingsBtn.setOutlineThickness(2);
    settingsBtn.setOutlineColor(sf::Color::Black);

    sf::Text settingsText("Settings", font, 18);
    settingsText.setFillColor(sf::Color::Black);
    settingsText.setPosition(settingsBtn.getPosition().x + 10, settingsBtn.getPosition().y + 5);

    // Buttons below the game board
    const float buttonWidth = 120;
    const float buttonHeight = 50;
    const float buttonSpacing = 40;

    float totalWidth = buttonWidth * 3 + buttonSpacing * 2;
    float buttonStartX = (mainwindow.getSize().x - totalWidth) / 2.f;
    float buttonY = startY + boardWidth + 40;

    sf::RectangleShape newGameBtn(sf::Vector2f(buttonWidth, buttonHeight));
    newGameBtn.setFillColor(sf::Color(0, 150, 255));
    newGameBtn.setPosition(buttonStartX, buttonY);

    sf::Text newGameText("New Game", font, 20);
    newGameText.setFillColor(sf::Color::White);
    newGameText.setPosition(newGameBtn.getPosition().x + 10, newGameBtn.getPosition().y + 10);

    sf::RectangleShape resumeBtn(sf::Vector2f(buttonWidth, buttonHeight));
    resumeBtn.setFillColor(sf::Color(0, 200, 120));
    resumeBtn.setPosition(buttonStartX + buttonWidth + buttonSpacing, buttonY);

    sf::Text resumeText("Resume", font, 20);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setPosition(resumeBtn.getPosition().x + 20, resumeBtn.getPosition().y + 10);

    sf::RectangleShape leaderboardBtn(sf::Vector2f(buttonWidth, buttonHeight));
    leaderboardBtn.setFillColor(sf::Color(255, 160, 50));
    leaderboardBtn.setPosition(buttonStartX + (buttonWidth + buttonSpacing) * 2, buttonY);

    sf::Text leaderboardText("Leaderboard", font, 20);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setPosition(leaderboardBtn.getPosition().x + 5, leaderboardBtn.getPosition().y + 10);

    // Menu loop
    while (mainwindow.isOpen())
    {
        sf::Event event;
        while (mainwindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mainwindow.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {

                auto mousePos = mainwindow.mapPixelToCoords(sf::Mouse::getPosition(mainwindow));

                if (resumeBtn.getGlobalBounds().contains(mousePos))
                {
                    std::cout << "Resume pressed\n";
                }
                else if (leaderboardBtn.getGlobalBounds().contains(mousePos))
                {

                    std::cout << "Leaderboard pressed\n";
                }
                else if (settingsBtn.getGlobalBounds().contains(mousePos))
                {
                    std::cout << "Settings pressed\n";
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                // xử lý phím W A S D
                if (event.key.code == sf::Keyboard::W) moveUp();
                if (event.key.code == sf::Keyboard::S) moveDown();
                if (event.key.code == sf::Keyboard::A) moveLeft();
                if (event.key.code == sf::Keyboard::D) moveRight();

                 addRandom();
            }
            


        }

        mainwindow.clear(sf::Color::Black);
        mainwindow.draw(scoreBox);
        mainwindow.draw(scoreText);
        mainwindow.draw(settingsBtn);
        mainwindow.draw(settingsText);
        drawBoard(mainwindow, startX, startY, tileSize, spacing, font);
        mainwindow.draw(newGameBtn);
        mainwindow.draw(newGameText);
        mainwindow.draw(resumeBtn);
        mainwindow.draw(resumeText);
        mainwindow.draw(leaderboardBtn);
        mainwindow.draw(leaderboardText);
        mainwindow.display();
    }
}
