// ScalianSudokuSolver.h
#ifndef SCALIANSUDOKUSOLVER_H
#define SCALIANSUDOKUSOLVER_H

#include <array>
#include <QDebug>

class ScalianSudoku;  // Forward declaration

class ScalianSudokuSolver
{
public:
    ScalianSudokuSolver(ScalianSudoku& sudokuInstance);

    virtual void solveSudoku(std::array<std::array<int, 9>, 9> &sudokuBoard);
    // Add other solving-related methods if needed

private:
    ScalianSudoku& sudokuInstance;
    bool solveSudokuRecursive(std::array<std::array<int, 9>, 9>& sudokuBoard, uint row, uint col);

};


#endif // SCALIANSUDOKUSOLVER_H
