#include "config.h"
#include <fstream>

int cellSize = 40;
int gridWidth = 20;
int gridHeight = 20;
MazeSize currentMazeSize = SMALL;

float bestTimes[3] = { 0.0f, 0.0f, 0.0f };

void setMazeSize(MazeSize size) {
    currentMazeSize = size;

    switch (size) {
    case SMALL:
        cellSize = 40;
        gridWidth = 20;
        gridHeight = 20;
        break;
    case MEDIUM:
        cellSize = 30;
        gridWidth = 26;
        gridHeight = 26;
        break;
    case LARGE:
        cellSize = 24;
        gridWidth = 34;
        gridHeight = 34;
        break;
    }
}
    