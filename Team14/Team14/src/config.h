#pragma once

struct Position
{
    int x, y;
};

struct Cell
{
    bool visited;
    bool topWall, bottomWall, leftWall, rightWall;
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

extern float bestTimes[3];


void saveBestTimesToFile();
void loadBestTimesFromFile();