#include "UndoRedo.h"
#include "Board.h"
#include <iostream>
#include <vector>

using namespace std;

const int MAX_HISTORY = 100; // Giới hạn số bước undo/redo
int undoIndex = -1;
int redoIndex = -1;

vector<vector<vector<int>>> undoStack(MAX_HISTORY, vector<vector<int>>()); 
vector<vector<vector<int>>> redoStack(MAX_HISTORY, vector<vector<int>>());

void saveState()
{
    if (undoIndex + 1 < MAX_HISTORY)
    {
        undoIndex++;
    }
    else
    {
        // Dịch các phần tử về trước để không vượt quá giới hạn
        for (int i = 0; i < MAX_HISTORY - 1; i++)
        {
            undoStack[i] = undoStack[i + 1];
        }
    }

    // Cập nhật kích thước nếu chưa có
    if (undoStack[undoIndex].empty())
    {
        undoStack[undoIndex] = vector<vector<int>>(boardSize, vector<int>(boardSize));
    }

    // Lưu trạng thái mới
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            undoStack[undoIndex][i][j] = board[i][j];
        }
    }

    // Khi có hành động mới, xóa redoStack
    redoIndex = -1;
}

void undoMove()
{
    if (undoIndex < 0)
    {
        cout << "Khong the Undo! Khong co trang thai truoc do.\n";
        return;
    }

    // Lưu trạng thái hiện tại vào redoStack trước khi undo
    if (redoIndex + 1 < MAX_HISTORY)
    {
        redoIndex++;
    }
    else
    {
        for (int i = 0; i < MAX_HISTORY - 1; i++)
        {
            redoStack[i] = redoStack[i + 1];
        }
    }

    // Cập nhật kích thước nếu cần
    if (redoStack[redoIndex].empty())
    {
        redoStack[redoIndex] = vector<vector<int>>(boardSize, vector<int>(boardSize));
    }

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            redoStack[redoIndex][i][j] = board[i][j];
        }
    }

    // Lấy trạng thái Undo
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j] = undoStack[undoIndex][i][j];
        }
    }

    undoIndex--; // Giảm chỉ số undo
}

void redoMove()
{
    if (redoIndex < 0)
    {
        cout << "Khong the Redo! Khong co trang thai sau do.\n";
        return;
    }

    // Lưu trạng thái hiện tại vào undoStack trước khi redo
    if (undoIndex + 1 < MAX_HISTORY)
    {
        undoIndex++;
    }
    else
    {
        for (int i = 0; i < MAX_HISTORY - 1; i++)
        {
            undoStack[i] = undoStack[i + 1];
        }
    }

    // Cập nhật kích thước nếu cần
    if (undoStack[undoIndex].empty())
    {
        undoStack[undoIndex] = vector<vector<int>>(boardSize, vector<int>(boardSize));
    }

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            undoStack[undoIndex][i][j] = board[i][j];
        }
    }

    // Lấy trạng thái Redo
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j] = redoStack[redoIndex][i][j];
        }
    }

    redoIndex--; // Giảm chỉ số redo
}
