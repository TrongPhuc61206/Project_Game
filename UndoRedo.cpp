#include "UndoRedo.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

stack<vector<vector<int>>> undoStack;
stack<vector<vector<int>>> redoStack;

// Lưu trạng thái hiện tại vào undoStack
void saveState()
{
    vector<vector<int>> temp(boardSize, vector<int>(boardSize));

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            temp[i][j] = board[i][j];
        }
    }
    undoStack.push(temp);
    while (!redoStack.empty())
        redoStack.pop(); // Khi có hành động mới, xóa redoStack
}

// Hoàn tác (Undo)
void undoMove()
{
    if (undoStack.empty())
    {
        cout << "Không thể Undo! Không có trạng thái trước đó.\n";
        return;
    }

    vector<vector<int>> temp(boardSize, vector<int>(boardSize));

    // Lưu trạng thái hiện tại vào redoStack trước khi undo
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            temp[i][j] = board[i][j];
        }
    }

    redoStack.push(temp);

    // Lấy trạng thái Undo
    vector<vector<int>> prevState = undoStack.top();
    undoStack.pop();

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j] = prevState[i][j];
        }
    }
}

// Làm lại (Redo)
void redoMove()
{
    if (redoStack.empty())
    {
        cout << "Không thể Redo! Không có trạng thái sau đó.\n";
        return;
    }

    vector<vector<int>> temp(boardSize, vector<int>(boardSize));

    // Lưu trạng thái hiện tại vào undoStack trước khi redo
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            temp[i][j] = board[i][j];
        }
    }
    undoStack.push(temp);

    // Lấy trạng thái Redo
    vector<vector<int>> nextState = redoStack.top();
    redoStack.pop();

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j] = nextState[i][j];
        }
    }
}
