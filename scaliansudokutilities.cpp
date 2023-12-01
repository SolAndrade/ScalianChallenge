#include "scaliansudoku.h"

#include <random>


bool ScalianSudoku::findEmptyCell(uint& row, uint& col)
{
    for (row = 0; row < 9; ++row)
    {
        for (col = 0; col < 9; ++col)
        {
            if (sudokuBoard[row][col] == 0)
            {
                return true;  // Found an empty cell
            }
        }
    }

    return false;  // No empty cell found
}

bool ScalianSudoku::isValidMove(uint row, uint col, int num)
{
    // Check if the number is not already present in the current row and column
    for (uint i = 0; i < 9; ++i)
    {
        if (sudokuBoard[row][i] == num || sudokuBoard[i][col] == num)
        {
            return false;  // Number already present in the row or column
        }
    }

    // Check if the number is not present in the 3x3 subgrid
    uint startRow = row - row % 3;
    uint startCol = col - col % 3;
    for (uint i = 0; i < 3; ++i)
    {
        for (uint j = 0; j < 3; ++j)
        {
            if (sudokuBoard[startRow + i][startCol + j] == num)
            {
                return false;  // Number already present in the subgrid
            }
        }
    }

    return true;  // The move is valid
}

bool ScalianSudoku::checkSudoku()
{
    qDebug() << "Checking Sudoku...";

    uint emptyRow, emptyCol;

    // Check if there are any empty cells
    if (findEmptyCell(emptyRow, emptyCol))
    {
        qDebug() << "Sudoku is incomplete. Found an empty cell at (" << emptyRow << "," << emptyCol << ")";
        return false;
    }

    // Additional checks or logic can be added here if needed

    qDebug() << "Sudoku is complete.";
    return true;
}

void ScalianSudoku::setEmptyBoard()
{
    std::vector<std::array<std::array<int, 9>, 9>> sudokuBoards = {
        {{
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0}
        }},
        };
    sudokuBoard = sudokuBoards[0];
}

void ScalianSudoku::setInitialSudoku()
{

    /*{{
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    }},*/
    std::vector<std::array<std::array<int, 9>, 9>> sudokuBoards = {
        {{
          {0, 9, 5, 0, 7, 1, 2, 3, 0},
          {7, 2, 0, 0, 0, 0, 0, 0, 4},
          {8, 0, 0, 5, 0, 0, 0, 0, 0},
          {6, 0, 8, 0, 0, 0, 7, 0, 0},
          {0, 0, 0, 0, 0, 6, 4, 0, 3},
          {0, 0, 0, 0, 3, 9, 0, 0, 6},
          {0, 8, 6, 0, 1, 0, 0, 0, 2},
          {2, 0, 0, 0, 4, 3, 0, 0, 5},
          {3, 4, 0, 0, 0, 0, 0, 0, 9}
        }},
        {{
          {0, 2, 0, 5, 1, 9, 6, 0, 0},
          {0, 0, 0, 0, 0, 2, 0, 0, 5},
          {7, 0, 0, 4, 0, 0, 0, 0, 0},
          {0, 3, 7, 0, 0, 0, 0, 0, 9},
          {5, 0, 0, 0, 4, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 5, 3, 1},
          {2, 0, 0, 0, 0, 0, 0, 0, 3},
          {1, 0, 0, 0, 9, 6, 0, 0, 4},
          {8, 7, 4, 0, 5, 0, 0, 0, 0}
        }},
        {{
          {0, 0, 0, 2, 3, 0, 0, 0, 0},
          {0, 0, 2, 0, 8, 5, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 7, 0, 4},
          {0, 9, 0, 0, 6, 0, 0, 7, 3},
          {0, 0, 0, 0, 0, 0, 4, 0, 0},
          {4, 6, 0, 3, 5, 0, 0, 0, 0},
          {0, 2, 0, 0, 0, 6, 0, 0, 7},
          {0, 0, 1, 0, 9, 0, 2, 3, 0},
          {0, 0, 0, 5, 0, 0, 0, 0, 0}
        }},
        {{
          {0, 0, 0, 0, 0, 0, 5, 0, 0},
          {9, 0, 0, 0, 0, 3, 0, 4, 7},
          {4, 0, 0, 0, 0, 0, 0, 0, 6},
          {0, 0, 6, 0, 7, 9, 0, 0, 4},
          {0, 0, 0, 2, 0, 0, 0, 0, 0},
          {0, 0, 8, 5, 0, 0, 7, 9, 0},
          {0, 0, 9, 8, 1, 2, 0, 0, 3},
          {0, 0, 0, 0, 5, 0, 0, 0, 0},
          {0, 0, 3, 0, 0, 0, 4, 0, 0}
        }},
        };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, sudokuBoards.size() - 1);
    int randomIndex = distr(gen);

    sudokuBoard = sudokuBoards[randomIndex];
}
