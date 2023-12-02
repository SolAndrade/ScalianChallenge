#include "scaliansudoku.h"

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
