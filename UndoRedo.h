#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include <vector>
using namespace std;

extern vector<vector<vector<int>>> undoStack;
extern vector<vector<vector<int>>> redoStack;

void saveState();
void undoMove();
void redoMove();

#endif // UNDO_REDO_H
