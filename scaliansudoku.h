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

    virtual void cleanSudoku();
    virtual void solveSudoku();
    virtual void setInitialSudoku();
    virtual bool solveSudokuRecursive();
    virtual bool findEmptyCell(uint& row, uint& col);
    virtual bool isValidMove(uint row, uint col, int num);
    virtual bool checkSudoku();
    virtual void setCell(uint rowId, uint colId, uint value);
    virtual void deleteCell(uint rowId, uint colId);

    ~ScalianSudoku();

protected:

    virtual void onDoubleClickInCell(uint rowId, uint colId);
    std::optional<QLabel*> getCell(uint rowId, uint colId);

    bool cleanCell(uint rowId, uint colId);
    bool writeCell(uint value, uint rowId, uint colId, QColor color = QColor(Qt::GlobalColor::black));
    void writeResult(const std::string &result, QColor color = QColor(Qt::GlobalColor::black));

    void onCleanSudoku();
    void onSolveSudoku();
    void onAccept();
    void onCancel();
    void onDelete();

private:    

    bool eventFilter(QObject *object, QEvent *event) override;
    std::optional<std::tuple<uint, uint>> getCoordinates(QObject *object);

    std::array<std::array<int, 9>, 9> sudokuBoard;
    QColor darkBlue{64, 122, 255};
    QColor lightBlue{230, 237, 255};

    Ui::ScalianSudoku *ui;
    bool emptySudoku;
};
#endif // SCALIANSUDOKU_H
