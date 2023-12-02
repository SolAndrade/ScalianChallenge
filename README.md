# <span style="color:#407AFF">Sudoku Solver Application</span>

## <span style="color:#90B1FE">Overview</span>

The Sudoku Solver Application is a Qt-based graphical user interface that allows users to play and solve Sudoku puzzles. The application includes a Sudoku board, a solver algorithm, and interactive features to enhance the user experience.

## <span style="color:#90B1FE">Table of Contents</span>
- [Features](#features)
- [Getting Started](#gettingStarted)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
- [How to Use](#howToUse)
    - [User Interface](#userInterface)
    - [Game Rules](#gameRules)
    - [Solver Algorithm](#solverAlgorithm)
- [UI Improvements](#uiImprovements)
- [License](#license)

## <span style="color:#90B1FE">Features</span>
- Interactive Sudoku board with clickable cells.
- Sudoku solver algorithm to automatically complete puzzles.
- User-friendly interface with visual cues for better usability.
- Dynamic UI improvements for an enhanced user experience.

## <span style="color:#90B1FE">Getting Started</span>
### <span style="color:#D4E1FF">Prerequisites</span>
- Qt framework installed on your system.
- C++ compiler compatible with the Qt version.

### <span style="color:#D4E1FF">Installation</span>
1. Clone the repository:

    git clone https://github.com/yourusername/SudokuSolver.git

2. Build the application using Qt Creator or your preferred Qt development environment.

3. Run the application.

## <span style="color:#90B1FE">How to Use</span>
### <span style="color:#D4E1FF">User Interface</span>
The application provides an intuitive user interface with the following components:

- **Sudoku Board:** A 9x9 grid where users can input their Sudoku puzzle or play interactively.
- **Interactive Controls:** Buttons to validate, solve, and reset the Sudoku board.
- **Status Display:** Information about the solving process and results.

### <span style="color:#D4E1FF">Game Rules</span>
Sudoku is a number puzzle game played on a 9x9 grid. The rules are simple:

1. Each row must contain the numbers 1 through 9 with no repetition.
2. Each column must contain the numbers 1 through 9 with no repetition.
3. Each of the nine 3x3 subgrids must contain the numbers 1 through 9 with no repetition.


### <span style="color:#D4E1FF">Solver Algorithm</span>
The application includes a backtracking algorithm to solve Sudoku puzzles. The solver checks each cell for a valid number based on the game rules, and if a solution exists, it fills in the entire board.

## <span style="color:#90B1FE">UI Improvements</span>
To enhance the user experience, the application includes the following UI improvements:

- **Cell Highlighting:** Selected cells are highlighted in medium blue for easy identification.
- **Error Feedback:** Cells with incorrect values are highlighted in red to alert the user.
- **Dynamic Background Colors:** Cells are visually categorized based on their status (empty, filled, error) to improve clarity.

## <span style="color:#90B1FE">License</span>
This project was developed as part of a code challenge presented by [Scalian Spain](https://www.scalian-spain.es/) and [42 Málaga Fundación Telefónica](https://www.42malaga.com/). The intellectual property rights of the challenge specifications and related materials belong to Scalian and 42 Málaga Fundación Telefónica.

## <span style="color:#90B1FE">Acknowledgments</span>
I would like say thank you to Scalian and 42 Málaga Fundación Telefónica for giving me the opportunity to participate in this engaging code challenge. The experience has been valuable, and I appreciate the chance to showcase my skills.

Despite me being new to the QT framework, the learning experience was enjoyable, and I am grateful for the chance to explore and work with a new technology.

Thank you for the enriching experience!

<span style="color:#90B1FE">made with ❤️ by <a style="color:#D4E1FF; text-decoration:none;" href="https://www.linkedin.com/in/sol-andrade/">Sol Andrade</a></span>