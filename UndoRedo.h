#pragma once
#include <stack>
#include <vector>

extern std::stack<std::vector<std::vector<int>>> undoStack;
extern std::stack<std::vector<std::vector<int>>> redoStack;

void saveState();
void undoMove();
void redoMove();
