
#include "game.h"
#include <iostream>
#include <ctime>
#include "Board.h"

using namespace std;
using namespace sf;

const int MAX_BOARD_SIZE = 10;
const int MIN_BOARD_SIZE = 4;

Font font;
Text newGameText, resumeGameText, settingsText, leaderboardText, backText, boardSizeText;

void initGame(int &boardSize, vector<vector<int>> &board)
{
    board = vector<vector<int>>(boardSize, vector<int>(boardSize, 0));
    srand(static_cast<unsigned>(time(0)));
    addRandom();
    addRandom();
}

void drawBoard(RenderWindow &window, const vector<vector<int>> &board, int boardSize)
{
    float tileSize = 600.0f / boardSize;
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            RectangleShape tile(Vector2f(tileSize, tileSize));
            tile.setPosition(Vector2f(j * tileSize, i * tileSize));
            tile.setFillColor(board[i][j] ? Color(238, 228, 218) : Color(204, 192, 179));
            window.draw(tile);
        }
    }
}

void drawGameOver(RenderWindow &window)
{
    Text gameOverText(font, "Game Over", 50);
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(Vector2f(200.f, 200.f));
    window.draw(gameOverText);
}

void initMenu()
{
    font.openFromFile("arial.ttf");

    newGameText.setFont(font);
    newGameText.setString("New Game");
    newGameText.setCharacterSize(40);
    newGameText.setPosition(Vector2f(200.f, 150.f));

    resumeGameText.setFont(font);
    resumeGameText.setString("Resume");
    resumeGameText.setCharacterSize(40);
    resumeGameText.setPosition(Vector2f(250.f, 250.f));

    leaderboardText.setFont(font);
    leaderboardText.setString("Leaderboard");
    leaderboardText.setCharacterSize(40);
    leaderboardText.setPosition(Vector2f(200.f, 260.f));

    settingsText.setFont(font);
    settingsText.setString("Settings");
    settingsText.setCharacterSize(40);
    settingsText.setPosition(Vector2f(250.f, 350.f));
}

void drawMainMenu(RenderWindow &window)
{
    window.draw(newGameText);
    window.draw(resumeGameText);
    window.draw(leaderboardText);
    window.draw(settingsText);
}

void handleMenuInput(Event &event, RenderWindow &window, bool &gameRunning, bool &inMenu,
                     bool &newGame, bool &resumeGame, bool &inSettings, bool &inLeaderboard)
{

    optional<Event> eventtop;
    if (eventtop && eventtop->getIf<Event::Closed>())
    {
        window.close();
    }
    else if (Mouse::isButtonPressed(Mouse::Button::Left))
    {
        // Get the global mouse position relative to the window
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Check for interactions with UI elements
        if (newGameText.getGlobalBounds().contains(mouseF))
        {
            newGame = true;
            inMenu = false;
            gameRunning = true;
        }
        else if (resumeGameText.getGlobalBounds().contains(mouseF))
        {
            resumeGame = true;
            inMenu = false;
            gameRunning = true;
        }
        else if (leaderboardText.getGlobalBounds().contains(mouseF))
        {
            inLeaderboard = true;
        }
        else if (settingsText.getGlobalBounds().contains(mouseF))
        {
            inSettings = true;
        }
    }

    // Example of setting mouse position relative to a window (if needed)
    Mouse::setPosition(Vector2i(100, 200), window);
}

void drawSettingsMenu(RenderWindow &window, int &boardSize)
{
    boardSizeText.setFont(font);
    boardSizeText.setString("Board Size: " + to_string(boardSize) + "x" + to_string(boardSize));
    boardSizeText.setCharacterSize(40);
    boardSizeText.setPosition(Vector2f(180.f, 150.f));

    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(40);
    backText.setPosition(Vector2f(250.f, 250.f));

    window.draw(boardSizeText);
    window.draw(backText);
}

void handleSettingsInput(Event &event, RenderWindow &window, int &boardSize, bool &inSettings)
{
    // Check if the window is being closed
    optional<Event> eventtop;
    if (eventtop && eventtop->getIf<Event::Closed>())
    {
        window.close();
    }

    // Detect mouse click and process interaction
    if (Mouse::isButtonPressed(Mouse::Button::Left))
    {
        Vector2i mousePos = Mouse::getPosition(window); // Get the mouse position relative to the window
        Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Check if the mouse click interacts with boardSizeText
        if (boardSizeText.getGlobalBounds().contains(mouseF))
        {
            boardSize = (boardSize < MAX_BOARD_SIZE) ? boardSize + 1 : MIN_BOARD_SIZE;
        }

        // Check if the mouse click interacts with backText
        if (backText.getGlobalBounds().contains(mouseF))
        {
            inSettings = false; // Exit settings mode
        }
    }
}

void drawLeaderboard(RenderWindow &window)
{
    Text leaderboard(font, "Leaderboard", 50);
    leaderboard.setFont(font);
    leaderboard.setString("Leaderboard");
    leaderboard.setCharacterSize(40);
    leaderboard.setPosition(Vector2f(150.f, 150.f));
    window.draw(leaderboard);

    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(40);
    backText.setPosition(Vector2f(250.f, 400.f));
    window.draw(backText);
}
void handleLeaderboardInput(RenderWindow &window, bool &inLeaderboard)
{
    // Check for left mouse button press
    if (Mouse::isButtonPressed(Mouse::Button::Left))
    {
        // Get the global mouse position relative to the window
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Check interaction with the "Back" button
        if (backText.getGlobalBounds().contains(mouseF))
        {
            inLeaderboard = false; // Exit the leaderboard view
        }
    }

    // Optionally set mouse position (example)
    Mouse::setPosition(Vector2i(100, 200), window); // Reset the cursor position
}
