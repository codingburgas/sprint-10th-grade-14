#include "config.h"


int cellSize = 40;
int gridWidth = 20;
int gridHeight = 20;
MazeSize currentMazeSize = SMALL;

void setMazeSize(MazeSize size) {
    currentMazeSize = size;

    switch (size) {
    case SMALL:
        cellSize = 40;
        gridWidth = 20;
        gridHeight = 20;
        break;
    case MEDIUM:
        cellSize = 26;
        gridWidth = 30;
        gridHeight = 30;
        break;
    case LARGE:
        cellSize = 20;
        gridWidth = 40;
        gridHeight = 40;
        break;
    }
}