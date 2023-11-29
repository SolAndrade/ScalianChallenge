#include "scaliansudoku.h"
#include "ui_scaliansudoku.h"
#include <random>
#include <QPixmap>
#include <QDebug>

ScalianSudoku::ScalianSudoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ScalianSudoku)
    , emptySudoku{true}
{
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    ui->setupUi(this);

    ui->FrameCells->setVisible(false);

    ui->LogoScalian->setPixmap(QPixmap(":/logo/scalian"));
    ui->LogoCampus->setPixmap(QPixmap(":/logo/campus42"));
    ui->LogoCampus->setScaledContents(true);

    int itemIdx = 0;
    uint rows = ui->Board->count();
    for(uint rowId = 0; rowId < rows; rowId++)
    {
        if(auto widget = ui->Board->itemAt(rowId)->widget())
        {
            if(widget->objectName().contains("separator"))
            {
                continue;
            }
        }
        auto row = ui->Board->itemAt(rowId)->layout();
        uint cells = row->count();
        for(uint cellId = 0; cellId < cells; cellId++)
        {
            auto cell = dynamic_cast<QLabel*>(row->itemAt(cellId)->widget());
            if(not cell)
            {
                continue;
            }

            cell->setText("");
            cell->setProperty("row", itemIdx/9);
            cell->setProperty("col", itemIdx%9);
            cell->installEventFilter(this);
            itemIdx++;
        }
    }

    connect(ui->cleanButton, &QPushButton::clicked, this, &ScalianSudoku::onCleanSudoku);
    connect(ui->solveButton, &QPushButton::clicked, this, &ScalianSudoku::onSolveSudoku);

    connect(ui->Accept, &QPushButton::clicked, this, &ScalianSudoku::onAccept);
    connect(ui->Cancel, &QPushButton::clicked, this, &ScalianSudoku::onCancel);
    connect(ui->Delete, &QPushButton::clicked, this, &ScalianSudoku::onDelete);
    // Fill the board with initial values
    setInitialSudoku();
}

void ScalianSudoku::cleanSudoku()
{
    qDebug() << "Borrar Sudoku";
}

void ScalianSudoku::solveSudoku()
{
    // Solve the Sudoku
    if (solveSudokuRecursive())
    {
        // If solution found, update UI
        for (uint row = 0; row < 9; ++row)
        {
            for (uint col = 0; col < 9; ++col)
            {
                writeCell(sudokuBoard[row][col], row, col, Qt::black);
            }
        }
    }
    else
    {
        // Handle case where no solution found
        writeResult("No solution found", QColor(Qt::GlobalColor::red));
    }
}

bool ScalianSudoku::solveSudokuRecursive()
{
    // Find empty cell
    uint row, col;
    return !findEmptyCell(row, col);

    // Try filling the empty cell with numbers 1 to 9
    for (int num = 1; num <= 9; ++num)
    {
        if (isValidMove(row, col, num))
        {
            // Fill the cell
            sudokuBoard[row][col] = num;

            // Recursively fill the rest of the board
            if (solveSudokuRecursive())
            {
                return true;  // If solution found, true
            }

            // If the move does not lead to a solution, backtrack
            sudokuBoard[row][col] = 0;
        }
    }

    return false;  // No valid number found for the current cell
}

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
    qDebug() << "check Sudoku";
    return false;
}

void ScalianSudoku::setInitialSudoku()
{
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
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, sudokuBoards.size() - 1);
    int randomIndex = distr(gen);

    sudokuBoard = sudokuBoards[randomIndex];

}

void ScalianSudoku::setCell(uint rowId, uint colId, uint value)
{
    qDebug() << "Set Cell (" << rowId << "," << colId << "): " << value;

    auto cell = getCell(rowId, colId);

    if (cell.has_value())
    {
        cell.value()->setText(QString::number(value));
    }
}

void ScalianSudoku::deleteCell(uint rowId, uint colId)
{
    qDebug() << "Delete Celda ("<< rowId << "," << colId << ")";
}

ScalianSudoku::~ScalianSudoku()
{
    delete ui;
}

void ScalianSudoku::onDoubleClickInCell(uint rowId, uint colId)
{
    ui->FrameCells->setProperty("row", rowId);
    ui->FrameCells->setProperty("col", colId);

    ui->RowTag->setText(QString::number(rowId));
    ui->ColTag->setText(QString::number(colId));
    ui->FrameCells->setVisible(true);
    ui->FrameControls->setVisible(false);
}

std::optional<QLabel*> ScalianSudoku::getCell(uint rowId, uint colId)
{
    if(rowId > 9 || colId > 9)
    {
        return std::nullopt;
    }

    if(colId > 5)
    {
        colId += 2;
    }
    else if(colId > 2)
    {
        colId += 1;
    }

    if(rowId > 5)
    {
        rowId += 2;
    }
    else if(rowId > 2)
    {
        rowId += 1;
    }

    auto row = ui->Board->itemAt(rowId)->layout();
    auto cell = dynamic_cast<QLabel*>(row->itemAt(colId)->widget());

    if(not cell)
    {
        return std::nullopt;
    }

    return cell;
}

bool ScalianSudoku::cleanCell(uint rowId, uint colId)
{
    auto cell = getCell(rowId, colId);
    if(cell.has_value())
    {
        QColor color(Qt::GlobalColor::black);
        cell.value()->setStyleSheet(QString("QLabel { color : rgb(%1,%2,%3); }").arg(color.red()).arg(color.green()).arg(color.blue()));
        cell.value()->setText("");
        return true;
    }

    return false;
}

bool ScalianSudoku::writeCell(uint valor, uint rowId, uint colId, QColor color)
{
    auto cell = getCell(rowId, colId);
    if(cell.has_value() && valor < 10)
    {
        cell.value()->setStyleSheet(QString("QLabel { color : rgb(%1,%2,%3); }").arg(color.red()).arg(color.green()).arg(color.blue()));
        cell.value()->setText(QString::number(valor));
        return true;
    }

    return false;
}

void ScalianSudoku::writeResult(const std::string &result, QColor color)
{
    ui->ResultTag->setText(result.c_str());
    ui->ResultTag->setStyleSheet(QString("QLabel { color : rgb(%1,%2,%3); }").arg(color.red()).arg(color.green()).arg(color.blue()));
}

void ScalianSudoku::onCleanSudoku()
{
    for(uint rowId = 0; rowId < 9; rowId++)
    {
        for(uint colId = 0; colId < 9; colId++)
        {
            cleanCell(rowId, colId);
        }
    }

    writeResult("");
    cleanSudoku();
}

void ScalianSudoku::onSolveSudoku()
{
    solveSudoku();
    bool result = checkSudoku();

    if(result)
    {
        writeResult("Correct", QColor(Qt::GlobalColor::green));
    }
    else
    {
        writeResult("Incorrect", QColor(Qt::GlobalColor::red));
    }
}

void ScalianSudoku::onAccept()
{
    uint row = ui->FrameCells->property("row").value<uint>();
    uint col = ui->FrameCells->property("col").value<uint>();
    uint value = ui->CellValue->value();
    ui->FrameCells->setVisible(false);
    ui->FrameControls->setVisible(true);
    setCell(row, col, value);
}

void ScalianSudoku::onCancel()
{
    ui->FrameCells->setVisible(false);
    ui->FrameControls->setVisible(true);
}

void ScalianSudoku::onDelete()
{
    uint row = ui->FrameCells->property("row").value<uint>();
    uint col = ui->FrameCells->property("col").value<uint>();
    ui->FrameCells->setVisible(false);
    ui->FrameControls->setVisible(true);
    cleanCell(row, col);
    deleteCell(row, col);
}

bool ScalianSudoku::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonDblClick)
    {
        if(emptySudoku)
        {
            auto coordinates = getCoordinates(object);
            if(coordinates.has_value())
            {
                uint row= std::get<0>(coordinates.value());
                uint col = std::get<1>(coordinates.value());
                onDoubleClickInCell(row, col);
            }
        }
        else
        {
            // Popup
        }
    }

    return QMainWindow::eventFilter(object, event);
}

std::optional<std::tuple<uint, uint>> ScalianSudoku::getCoordinates(QObject *object)
{
    if(object)
    {
        auto label = dynamic_cast<QLabel*>(object);
        if(label)
        {
            uint row = object->property("row").value<uint>();
            uint col = object->property("col").value<uint>();
            return std::tuple<int,int>{row,col};
        }
    }

    return std::nullopt;
}

