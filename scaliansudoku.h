#ifndef SCALIANSUDOKU_H
#define SCALIANSUDOKU_H

#include <QMainWindow>
#include <optional>
#include <tuple>
#include <QLabel>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class ScalianSudoku; }
QT_END_NAMESPACE

class ScalianSudoku : public QMainWindow
{
    Q_OBJECT

public:
    ScalianSudoku(QWidget *parent = nullptr);

    // scaliansudokusolver.cpp
    virtual void solveSudoku();
    virtual bool solveSudokuRecursive();

    //scaliansudokuutilities.cpp
    virtual void setInitialSudoku();
    virtual bool findEmptyCell(uint& row, uint& col);
    virtual bool isValidMove(uint row, uint col, int num);
    virtual bool checkSudoku();
    virtual bool isValidBoard();
    virtual bool checkDuplicates(uint row, uint col, uint value);
    virtual void onRandomValues();

    //scaliansudoku_ui.cpp
    virtual void setEmptyBoard();
    virtual void setAllCellBg();
    virtual void printSudokuBoard();

    //scaliansudoku.cpp
    virtual void cleanSudoku();
    virtual void setCell(uint rowId, uint colId, uint value, QColor color);
    virtual void deleteCell(uint rowId, uint colId);
    virtual void writeResult(const std::string &result, QColor color = QColor(Qt::GlobalColor::black));

    // Sudoku Board Structure
    std::array<std::array<int, 9>, 9> sudokuBoard;

    // COLORS
    QColor darkBlue{64, 122, 255};
    QColor lightBlue{230, 237, 255};
    QColor mediumBlue{144, 177, 254};
    QColor mediumLightBlue{212, 225, 255};
    QColor darkRed{209, 35, 47};
    QColor mediumRed{228, 98, 107};

    ~ScalianSudoku();

protected:

    virtual void onDoubleClickInCell(uint rowId, uint colId);
    std::optional<QLabel*> getCell(uint rowId, uint colId);

    bool cleanCell(uint rowId, uint colId);

    void onCleanSudoku();
    void onSolveSudoku();
    void onAccept();
    void onCancel();
    void onDelete();

private:
    bool eventFilter(QObject *object, QEvent *event) override;
    std::optional<std::tuple<uint, uint>> getCoordinates(QObject *object);

    Ui::ScalianSudoku *ui;
    bool emptySudoku;
};
#endif // SCALIANSUDOKU_H
