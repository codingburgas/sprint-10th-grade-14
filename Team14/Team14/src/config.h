#pragma once

struct Position
{
    int x, y;
};

extern int cellSize;
extern int gridWidth;
extern int gridHeight;


enum MazeSize {
    SMALL = 0,
    MEDIUM,
    LARGE
};

extern MazeSize currentMazeSize;
void setMazeSize(MazeSize size);