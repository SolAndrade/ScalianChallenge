#include "scaliansudoku.h"
#include "ui_scaliansudoku.h"
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
    ui->Logo42->setPixmap(QPixmap(":/logo/campus42"));
    ui->Logo42->setScaledContents(true);
    ui->LogoScalian->setScaledContents(true);

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
    connect(ui->RandomValues, &QPushButton::clicked, this, &ScalianSudoku::onRandomValues);

    // Fill the board with null values
    setEmptyBoard();
    // Set bg colors
    setAllCellBg();
}

void ScalianSudoku::cleanSudoku()
{
    qDebug() << "Borrar Sudoku";

    // Iterate over all cells in sudokuBoard
    for (uint rowId = 0; rowId < 9; ++rowId)
    {
        for (uint colId = 0; colId < 9; ++colId)
        {
            sudokuBoard[rowId][colId] = 0;  // Set cell value to 0

            // Update UI to reflect the changes
            auto cell = getCell(rowId, colId);
            if (cell.has_value())
            {
                cell.value()->setText("");  // Clear text in QLabel
                cell.value()->setStyleSheet(QString("background-color : rgb(%1,%2,%3);")
                                                .arg(lightBlue.red()).arg(lightBlue.green()).arg(lightBlue.blue()));
            }
        }
    }
}

void ScalianSudoku::setCell(uint rowId, uint colId, uint value, QColor color)
{
    auto cell = getCell(rowId, colId);

    if (cell.has_value())
    {
        cell.value()->setText(QString::number(value));
        cell.value()->setStyleSheet(QString("QLabel { color : rgb(%1,%2,%3); background-color : rgb(%4,%5,%6); }")
                                        .arg(color.red()).arg(color.green()).arg(color.blue())
                                        .arg(lightBlue.red()).arg(lightBlue.green()).arg(lightBlue.blue()));
        if (checkDuplicates(rowId, colId, value)) {
            // If duplicates found, set the cell with red background
            cell.value()->setStyleSheet(QString("QLabel { color : rgb(%1,%2,%3); background-color : rgb(%4,%5,%6); }")
                                            .arg(darkRed.red()).arg(darkRed.green()).arg(darkRed.blue())
                                            .arg(mediumRed.red()).arg(mediumRed.green()).arg(mediumRed.blue()));
        }
    }
    sudokuBoard[rowId][colId] = value;
}

void ScalianSudoku::deleteCell(uint rowId, uint colId)
{
    auto cell = getCell(rowId, colId);

    if (cell.has_value())
    {
        // Clear the text in the QLabel
        cell.value()->setText("");

        sudokuBoard[rowId][colId] = 0;

        if (cell.value()->text().isEmpty())
        {
            cell.value()->setStyleSheet(QString("background-color : rgb(%4,%5,%6); }")
                                            .arg(lightBlue.red()).arg(lightBlue.green()).arg(lightBlue.blue()));
        }
    }
}

ScalianSudoku::~ScalianSudoku()
{
    delete ui;
}

void ScalianSudoku::onDoubleClickInCell(uint rowId, uint colId)
{
    setAllCellBg();

    auto cell = getCell(rowId, colId);

    // Set background color for cells in the same row and column
    for (uint i = 0; i < 9; ++i) {
        auto cellInRow = getCell(rowId, i);
        auto cellInCol = getCell(i, colId);

        if (cellInRow) {
            cellInRow.value()->setStyleSheet(QString("background-color : rgb(%1,%2,%3); }")
                                                 .arg(mediumLightBlue.red()).arg(mediumLightBlue.green()).arg(mediumLightBlue.blue()));
        }

        if (cellInCol && i != rowId) {
            cellInCol.value()->setStyleSheet(QString("background-color : rgb(%1,%2,%3); }")
                                                 .arg(mediumLightBlue.red()).arg(mediumLightBlue.green()).arg(mediumLightBlue.blue()));
        }
    }

    if (cell) {
        cell.value()->setStyleSheet(QString("background-color : rgb(%1,%2,%3); }")
                                        .arg(mediumBlue.red()).arg(mediumBlue.green()).arg(mediumBlue.blue()));
    }

    ui->FrameCells->setProperty("row", rowId);
    ui->FrameCells->setProperty("col", colId);

    ui->RowTag->setText(QString::number(rowId+1));
    ui->ColTag->setText(QString::number(colId+1));
    ui->FrameCells->setVisible(true);
    ui->FrameControls->setVisible(false);
}

void ScalianSudoku::onRandomValues(){
    setInitialSudoku();
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
        sudokuBoard[rowId][colId] = 0;
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
}

void ScalianSudoku::onAccept()
{
    uint row = ui->FrameCells->property("row").value<uint>();
    uint col = ui->FrameCells->property("col").value<uint>();
    uint value = ui->CellValue->value();

    auto cell = getCell(row, col);

    if (!checkDuplicates(row, col, value)) {
        // If no duplicates, set the cell with default colors
        cell.value()->setStyleSheet(QString("background-color : rgb(%4,%5,%6); }")
                                        .arg(lightBlue.red()).arg(lightBlue.green()).arg(lightBlue.blue()));
        setCell(row, col, value, darkBlue);
    } else {
        // If duplicates found, set the cell with red background
        cell.value()->setStyleSheet(QString("background-color : rgb(%4,%5,%6); }")
                                        .arg(mediumRed.red()).arg(mediumRed.green()).arg(mediumRed.blue()));
        setCell(row, col, value, QColor(Qt::GlobalColor::red));
    }

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

