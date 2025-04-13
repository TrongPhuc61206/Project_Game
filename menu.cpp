#include <SFML/Graphics.hpp>
#include <iostream>

void showMainMenu(sf::RenderWindow &mainwindow)
{
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Cannot load font!\n";
        return; // Thoát sớm nếu không tải được font
    }

    // Score box
    sf::RectangleShape scoreBox(sf::Vector2f(150, 60));
    scoreBox.setFillColor(sf::Color(200, 200, 200));
    scoreBox.setPosition(20, 20);
    scoreBox.setOutlineThickness(2);
    scoreBox.setOutlineColor(sf::Color::Black);

    sf::Text scoreText("SCORE\n1234", font, 20);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(30, 25);

    // Settings button
    sf::RectangleShape settingsBtn(sf::Vector2f(100, 40));
    settingsBtn.setFillColor(sf::Color(180, 180, 180));
    settingsBtn.setPosition(480, 30);
    settingsBtn.setOutlineThickness(2);
    settingsBtn.setOutlineColor(sf::Color::Black);

    sf::Text settingsText("Settings", font, 18);
    settingsText.setFillColor(sf::Color::Black);
    settingsText.setPosition(490, 38);

    // Game board placeholder
    sf::RectangleShape boardArea(sf::Vector2f(500, 500));
    boardArea.setFillColor(sf::Color(230, 230, 230));
    boardArea.setOutlineThickness(2);
    boardArea.setOutlineColor(sf::Color::Black);
    boardArea.setPosition(50, 100);

    // Buttons
    sf::RectangleShape newGameBtn(sf::Vector2f(120, 50));
    newGameBtn.setFillColor(sf::Color(0, 150, 255));
    newGameBtn.setPosition(80, 630);

    sf::Text newGameText("New Game", font, 20);
    newGameText.setFillColor(sf::Color::White);
    newGameText.setPosition(95, 640);

    sf::RectangleShape resumeBtn(sf::Vector2f(120, 50));
    resumeBtn.setFillColor(sf::Color(0, 200, 120));
    resumeBtn.setPosition(240, 630);

    sf::Text resumeText("Resume", font, 20);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setPosition(265, 640);

    sf::RectangleShape leaderboardBtn(sf::Vector2f(140, 50));
    leaderboardBtn.setFillColor(sf::Color(255, 160, 50));
    leaderboardBtn.setPosition(400, 630);

    sf::Text leaderboardText("Leaderboard", font, 20);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setPosition(415, 640);

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

                if (newGameBtn.getGlobalBounds().contains(mousePos))
                {
                    std::cout << "New Game pressed\n";
                    // Start a new game
                }
                else if (resumeBtn.getGlobalBounds().contains(mousePos))
                {
                    std::cout << "Resume pressed\n";
                    // Resume game logic
                }
                else if (leaderboardBtn.getGlobalBounds().contains(mousePos))
                {
                    std::cout << "Leaderboard pressed\n";
                    // Show leaderboard
                }
                else if (settingsBtn.getGlobalBounds().contains(mousePos))
                {
                    std::cout << "Settings pressed\n";
                    // Open settings
                }
            }
        }

        mainwindow.draw(scoreBox);
        mainwindow.draw(scoreText);
        mainwindow.draw(settingsBtn);
        mainwindow.draw(settingsText);
        mainwindow.draw(boardArea);
        mainwindow.draw(newGameBtn);
        mainwindow.draw(newGameText);
        mainwindow.draw(resumeBtn);
        mainwindow.draw(resumeText);
        mainwindow.draw(leaderboardBtn);
        mainwindow.draw(leaderboardText);
        mainwindow.display();
    }
}
