#include "UserAuth.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;
User *root = nullptr;

// Function to delete entire tree
void deleteTree(User *node)
{
    if (node)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

const int k = 101;               // Hash table size
vector<string> hashTable(k, ""); // Storage array

// Password Hash Function
string hashPassword(const string &password)
{
    int hashValue = 0;

    for (int i = 0; i < password.length(); i++)
    {
        hashValue = hashValue + password[i];
    }

    // Lấy vị trí băm ban đầu
    int index = hashValue % k;

    while (hashTable[index] != "")
    {
        index = (index + 1) % k;
    }

    hashTable[index] = password;

    string hashedStr = "";
    for (int i = 0; i < password.length(); i++)
    {
        char c = 'A' + (password[i] % 26);
        hashedStr += c;
    }

    return hashedStr;
}

// Insert function into BST
void insert(User *&node, const string &username, const string &passwordHash)
{
    if (node == nullptr)
    {
        node = new User{username, passwordHash, nullptr, nullptr};
        return;
    }

    if (username < node->username)
        insert(node->left, username, passwordHash);
    insert(node->right, username, passwordHash);
}

bool usernameExists(User *node, const string &username)
{
    if (!node)
        return false;
    if (node->username == username)
        return true;
    return username < node->username
               ? usernameExists(node->left, username)
               : usernameExists(node->right, username);
}

// Register new account
bool registerUser(const string &username, const string &password)
{
    if (usernameExists(root, username))
    {
        cout << "Username already taken!\n";
        return false;
    }
    string passwordHash = hashPassword(password);
    insert(root, username, passwordHash);
    cout << "User " << username << " registered successfully!\n";
    return true;
}

// Search for users in BST
bool search(User *node, const string &username, const string &password)
{
    if (!node)
        return false;
    if (node->username == username)
        return node->passwordHash == hashPassword(password);
    return username < node->username ? search(node->left, username, password) : search(node->right, username, password); // Tìm kiếm trong BST
}

// Login
bool loginUser(const string &username, const string &password)
{
    return search(root, username, password);
}

void saveUserRecursive(User *node, ofstream &file)
{
    if (node == nullptr)
        return; // If node is empty then exit

    file << node->username << " " << node->passwordHash << endl;

    saveUserRecursive(node->left, file);
    saveUserRecursive(node->right, file);
}

// Save user list to file
void saveUsersToFile()
{
    ofstream file("users.txt", ios::app);
    if (!file)
        return;

    saveUserRecursive(root, file);

    file.close();
}

// Load list from file
void loadUsersFromFile()
{
    ifstream file("users.txt");
    if (!file)
        return;

    string username, passwordHash;
    while (file >> username >> passwordHash)
    {
        insert(root, username, passwordHash);
    }
    file.close();
}

bool showLoginOrRegisterScreen(std::string &outUsername)
{
    sf::RenderWindow window(sf::VideoMode(600, 450), "Welcome 2048", sf::Style::Close);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/background1.png"))
    {
        std::cerr << "Không thể load background!\n";
        return false;
    }
    sf::Sprite background(backgroundTexture);
    background.setScale(
        600.f / backgroundTexture.getSize().x,
        450.f / backgroundTexture.getSize().y);

    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Không thể load font!\n";
        return false;
    }

    // Title
    sf::Text title("Welcome 2048", font, 32);
    title.setFillColor(sf::Color(255, 255, 255));
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2);
    title.setPosition(160, 30);

    // Username label and box
    sf::Text userLabel("Username ", font, 20);
    userLabel.setFillColor(sf::Color::White);
    userLabel.setPosition(100, 90);

    sf::RectangleShape usernameBox(sf::Vector2f(400, 35));
    usernameBox.setPosition(100, 120);
    usernameBox.setFillColor(sf::Color(255, 255, 255, 200));
    usernameBox.setOutlineThickness(1);
    usernameBox.setOutlineColor(sf::Color::Black);

    // Password label and box
    sf::Text passLabel("Password ", font, 20);
    passLabel.setFillColor(sf::Color::White);
    passLabel.setPosition(100, 170);

    sf::RectangleShape passwordBox(sf::Vector2f(400, 35));
    passwordBox.setPosition(100, 200);
    passwordBox.setFillColor(sf::Color(255, 255, 255, 200));
    passwordBox.setOutlineThickness(1);
    passwordBox.setOutlineColor(sf::Color::Black);

    // Feedback text
    sf::Text feedbackText("", font, 16);
    feedbackText.setFillColor(sf::Color::Red);
    feedbackText.setPosition(100, 250);

    // Buttons
    sf::RectangleShape registerBtn(sf::Vector2f(150, 45));
    registerBtn.setPosition(100, 320);
    registerBtn.setFillColor(sf::Color(0, 180, 100));

    sf::Text registerText("Register", font, 22);
    registerText.setFillColor(sf::Color::White);
    registerText.setPosition(135, 328);

    sf::RectangleShape loginBtn(sf::Vector2f(150, 45));
    loginBtn.setPosition(350, 320);
    loginBtn.setFillColor(sf::Color(0, 120, 250));

    sf::Text loginText("Login", font, 22);
    loginText.setFillColor(sf::Color::White);
    loginText.setPosition(395, 328);

    std::string usernameInput = "", passwordInput = "";
    bool typingUsername = false, typingPassword = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return false;

            if (event.type == sf::Event::MouseButtonPressed)
            {
                auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                typingUsername = usernameBox.getGlobalBounds().contains(pos);
                typingPassword = passwordBox.getGlobalBounds().contains(pos);

                if (registerBtn.getGlobalBounds().contains(pos))
                {
                    if (registerUser(usernameInput, passwordInput))
                    {
                        feedbackText.setString("Dang ky thanh cong!");
                        feedbackText.setFillColor(sf::Color::Green);
                        saveUsersToFile();
                    }
                    else
                    {
                        feedbackText.setString("Username da ton tai");
                        feedbackText.setFillColor(sf::Color::Red);
                    }
                }

                if (loginBtn.getGlobalBounds().contains(pos))
                {
                    if (loginUser(usernameInput, passwordInput))
                    {
                        feedbackText.setString("Dang nhap thanh cong");
                        feedbackText.setFillColor(sf::Color::Green);
                        outUsername = usernameInput;
                        window.close();
                        return true;
                    }
                    else
                    {
                        feedbackText.setString("Sai username hoặc password!");
                        feedbackText.setFillColor(sf::Color::Red);
                    }
                }
            }

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8)
                {
                    if (typingUsername && !usernameInput.empty())
                        usernameInput.pop_back();
                    if (typingPassword && !passwordInput.empty())
                        passwordInput.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != 13)
                {
                    char ch = static_cast<char>(event.text.unicode);
                    if (typingUsername)
                        usernameInput += ch;
                    if (typingPassword)
                        passwordInput += ch;
                }
            }
        }

        // Draw UI
        window.clear();
        window.draw(background);
        window.draw(title);
        window.draw(userLabel);
        window.draw(usernameBox);
        window.draw(passLabel);
        window.draw(passwordBox);
        window.draw(feedbackText);
        window.draw(registerBtn);
        window.draw(registerText);
        window.draw(loginBtn);
        window.draw(loginText);

        sf::Text userText(usernameInput, font, 18);
        userText.setPosition(usernameBox.getPosition().x + 10, usernameBox.getPosition().y + 6);
        userText.setFillColor(sf::Color::Black);
        window.draw(userText);

        sf::Text passText(std::string(passwordInput.length(), '*'), font, 18);
        passText.setPosition(passwordBox.getPosition().x + 10, passwordBox.getPosition().y + 6);
        passText.setFillColor(sf::Color::Black);
        window.draw(passText);

        window.display();
    }

    return false;
}
