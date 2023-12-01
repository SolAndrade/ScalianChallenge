#include "scaliansudoku.h"

void ScalianSudoku::solveSudoku()
{
    //setInitialSudoku();
    // Solve the Sudoku
    qDebug() << "Solving Sudoku...";
    //setInitialSudoku();
    // Solve the Sudoku
    if (solveSudokuRecursive())
    {
        qDebug() << "Solution found!";
    }
    else
    {
        // Handle case where no solution found
        qDebug() << "No solution found!";
        writeResult("IMPOSSIBLE", QColor(Qt::GlobalColor::red));
    }
    qDebug() << "Solving process complete.";
}

bool ScalianSudoku::solveSudokuRecursive()
{
    // Find empty cell
    uint row, col;
    if (!findEmptyCell(row, col))
    {
        return true;  // If no empty cell is found, the puzzle is solved
    }

    // Try filling the empty cell with numbers 1 to 9
    //qDebug() << "empty cell to fill:(" << row << "," << col << "): ";
    for (int num = 1; num <= 9; ++num)
    {
        if (isValidMove(row, col, num))
        {
            // Fill the cell
            sudokuBoard[row][col] = num;
            setCell(row, col, num, Qt::black);

            // Recursively fill the rest of the board
            if (solveSudokuRecursive())
            {
                return true;  // If solution found, true
            }

            // If the move does not lead to a solution, backtrack
            sudokuBoard[row][col] = 0;
        }
        //qDebug() << "no valid move for(" << num << "): " << sudokuBoard[row][col];

    }

    return false;  // No valid number found for the current cell
}
