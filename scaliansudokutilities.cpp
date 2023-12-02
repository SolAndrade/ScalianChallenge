#include "scaliansudoku.h"
#include <unordered_set>
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
    for (uint row = 0; row < 9; ++row) {
        for (uint col = 0; col < 9; ++col) {
            std::optional<QLabel*> cell = getCell(row, col);

            if (cell) {
                deleteCell(row, col);
            }
        }
    }
}

void ScalianSudoku::setInitialSudoku()
{
    setEmptyBoard();
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
    for (uint row = 0; row < 9; ++row) {
        for (uint col = 0; col < 9; ++col) {
            // Assuming getCell function returns the cell widget or structure
            std::optional<QLabel*> cell = getCell(row, col);

            if (cell && sudokuBoard[row][col] != 0) {
                setCell(row, col, sudokuBoard[row][col], darkBlue);
            }
        }
    }
}

bool ScalianSudoku::isValidBoard()
{
    // Check rows and columns
    for (uint i = 0; i < 9; ++i)
    {
        std::unordered_set<int> rowSet;
        std::unordered_set<int> colSet;

        for (uint j = 0; j < 9; ++j)
        {
            // Check rows
            if (rowSet.find(sudokuBoard[i][j]) != rowSet.end())
                return false;
            if (sudokuBoard[i][j] != 0)
                rowSet.insert(sudokuBoard[i][j]);

            // Check columns
            if (colSet.find(sudokuBoard[j][i]) != colSet.end())
                return false;
            if (sudokuBoard[j][i] != 0)
                colSet.insert(sudokuBoard[j][i]);
        }
    }

    // Check regions
    for (uint i = 0; i < 9; i += 3)
    {
        for (uint j = 0; j < 9; j += 3)
        {
            std::unordered_set<int> regionSet;

            for (uint row = 0; row < 3; ++row)
            {
                for (uint col = 0; col < 3; ++col)
                {
                    int num = sudokuBoard[i + row][j + col];

                    // Check regions
                    if (regionSet.find(num) != regionSet.end())
                        return false;
                    if (num != 0)
                        regionSet.insert(num);
                }
            }
        }
    }

    return true;
}

void ScalianSudoku::setAllCellBg() {
    for (uint row = 0; row < 9; ++row) {
        for (uint col = 0; col < 9; ++col) {
            std::optional<QLabel*> cell = getCell(row, col);

            if (cell) {
                if (sudokuBoard[row][col] != 0) {
                    if (checkDuplicates(row, col, sudokuBoard[row][col])) {
                        // If duplicates found, set the cell with darkRed color and mediumRed background
                        cell.value()->setStyleSheet(QString("QLabel { color : rgb(%1,%2,%3); background-color : rgb(%4,%5,%6); }")
                                                        .arg(darkRed.red()).arg(darkRed.green()).arg(darkRed.blue())
                                                        .arg(mediumRed.red()).arg(mediumRed.green()).arg(mediumRed.blue()));
                    } else {
                        // If the cell is not empty and no duplicates, set color to darkBlue and background to lightBlue
                        cell.value()->setStyleSheet(QString("QLabel { color : rgb(%1,%2,%3); background-color : rgb(%4,%5,%6); }")
                                                        .arg(darkBlue.red()).arg(darkBlue.green()).arg(darkBlue.blue())
                                                        .arg(lightBlue.red()).arg(lightBlue.green()).arg(lightBlue.blue()));
                    }
                } else {
                    // If the cell is empty, set only the background color to lightBlue
                    cell.value()->setStyleSheet(QString("QLabel { background-color : rgb(%1,%2,%3); }")
                                                    .arg(lightBlue.red()).arg(lightBlue.green()).arg(lightBlue.blue()));
                }
            }
        }
    }
}

bool ScalianSudoku::checkDuplicates(uint row, uint col, uint value)
{
    // Check duplicates in row
    for (uint i = 0; i < 9; ++i) {
        if (i != col && sudokuBoard[row][i] == value) {
            qDebug() << "Duplicate in row: (" << row << ", " << i << ")";
            return true;
        }
    }

    // Check duplicates in column
    for (uint i = 0; i < 9; ++i) {
        if (i != row && sudokuBoard[i][col] == value) {
            qDebug() << "Duplicate in column: (" << i << ", " << col << ")";
            return true;
        }
    }

    // Check duplicates in region
    uint startRow = 3 * (row / 3);
    uint startCol = 3 * (col / 3);
    for (uint i = startRow; i < startRow + 3; ++i) {
        for (uint j = startCol; j < startCol + 3; ++j) {
            if (i != row && j != col && sudokuBoard[i][j] == value) {
                qDebug() << "Duplicate in region: (" << i << ", " << j << ")";
                return true;
            }
        }
    }

    return false; // No duplicates found
}

void ScalianSudoku::printSudokuBoard()
{
    qDebug() << "Sudoku Board:";
    for (uint row = 0; row < 9; ++row) {
        QString rowString;
        for (uint col = 0; col < 9; ++col) {
            rowString += QString::number(sudokuBoard[row][col]) + " ";
        }
        qDebug() << rowString.trimmed();
    }
}
