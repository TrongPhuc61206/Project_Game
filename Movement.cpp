#include "Movement.h"
#include <iostream>
#include "Board.h"
#include "Queue.h"
#include "UndoRedo.h"
using namespace std;

void clearQueue()
{
    frontIndex = 0;
    rearIndex = -1;
    sizequeue = 0;
}

void moveLeft()
{
    saveState();
    for (int i = 0; i < boardSize; i++)
    {
        clearQueue();
        frontIndex = 0, rearIndex = -1, sizequeue = 0; // Reset queue for each row
        for (int j = 0; j < boardSize; j++)
        {
            if (board[i][j] != 0)
            {
                if (sizequeue > 0 && queue[rearIndex] == board[i][j])
                {
                    queue[rearIndex] *= 2; // If 2 cells are equal, merge the cells
                }
                else
                {
                    enqueue(board[i][j]); // Add to queue
                }
            }
        }
        // Update row i
        for (int j = 0; j < boardSize; j++)
        {
            if (j < sizequeue)
            {
                board[i][j] = queue[frontIndex + j];
            }
            else
            {
                board[i][j] = 0; // Fill in 0 in the blank box
            }
        }
    }
}

void moveRight()
{
    saveState();
    for (int i = 0; i < boardSize; i++)
    {
        clearQueue();
        frontIndex = 0, rearIndex = -1, sizequeue = 0; // Reset queue for each row
        for (int j = boardSize - 1; j >= 0; j--)
        {
            if (board[i][j] != 0)
            {
                if (sizequeue > 0 && queue[rearIndex] == board[i][j])
                {
                    queue[rearIndex] *= 2; // If 2 cells are equal, merge the cells.
                }
                else
                {
                    enqueue(board[i][j]); // Add to queue
                }
            }
        }
        // Update row i
        for (int j = 0; j < boardSize; j++)
        {
            if (j < sizequeue)
            {
                board[i][boardSize - 1 - j] = queue[frontIndex + j];
            }
            else
            {
                board[i][boardSize - 1 - j] = 0; // Fill in 0 in the blank box
            }
        }
    }
}

void moveUp()
{
    saveState();
    for (int j = 0; j < boardSize; j++)
    {
        clearQueue();
        frontIndex = 0, rearIndex = -1, sizequeue = 0; // Reset queue for each column
        for (int i = 0; i < boardSize; i++)
        {
            if (board[i][j] != 0)
            {
                if (sizequeue > 0 && queue[rearIndex] == board[i][j])
                {
                    queue[rearIndex] *= 2; // If 2 cells are equal, merge the cells
                }
                else
                {
                    enqueue(board[i][j]); // Add to queue
                }
            }
        }
        // Update column j
        for (int i = 0; i < boardSize; i++)
        {
            if (i < sizequeue)
            {
                board[i][j] = queue[frontIndex + i];
            }
            else
            {
                board[i][j] = 0; // Fill in 0 in the blank box
            }
        }
    }
}

void moveDown()
{
    saveState();
    for (int j = 0; j < boardSize; j++)
    {
        clearQueue();
        frontIndex = 0, rearIndex = -1, sizequeue = 0; // Reset queue for each column
        for (int i = boardSize - 1; i >= 0; i--)
        {
            if (board[i][j] != 0)
            {
                if (sizequeue > 0 && queue[rearIndex] == board[i][j])
                {
                    queue[rearIndex] *= 2; // If 2 cells are equal, merge the cells.
                }
                else
                {
                    enqueue(board[i][j]); // Add to queue
                }
            }
        }
        // Update column j
        for (int i = 0; i < boardSize; i++)
        {
            if (i < sizequeue)
            {
                board[boardSize - 1 - i][j] = queue[frontIndex + i];
            }
            else
            {
                board[boardSize - 1 - i][j] = 0; // Fill in 0 in the blank box
            }
        }
    }
}

bool hasEmptyTile()
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board[i][j] == 0)
                return true; // Found a blank cell
        }
    }
    return false;
}

bool canMerge()
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if ((i + 1 < boardSize && board[i][j] == board[i + 1][j]) ||
                (j + 1 < boardSize && board[i][j] == board[i][j + 1]))
                return true; // Cells can be merged.
        }
    }
    return false;
}

bool canMove()
{
    // Check the winning condition (2048) first
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board[i][j] == 2048)
            {
                cout << "Chuc mung, ban da dat 2024" << endl;
                return true; // Allows resumption of play after win
            }
        }
    }

    // Check for empty cells or cell merging
    if (hasEmptyTile() || canMerge())
        return true;

    return false;
}
