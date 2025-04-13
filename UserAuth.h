#pragma once

#include <SFML/Graphics.hpp>

#include <string>
using namespace std;

// Data structure for User
struct User
{
    string username;
    string passwordHash;
    User *left;
    User *right;
};

// Login/Registration Handling Functions
bool registerUser(const string &username, const string &password);
bool loginUser(const string &username, const string &password);
bool search(User *node, const string &username, const string &password);
void saveUsersToFile();
void loadUsersFromFile();
bool showLoginOrRegisterScreen(string&);
