#pragma once

#include "utils.h"
#include "config.h"

struct Cell
{
	bool visited;
	bool topWall, bottomWall, leftWall, rightWall;
};

// Increase array size to handle large mazes safely
extern Cell maze[41][41];  // Changed from [40][40] to [41][41]
extern Position goal;

void initializeMaze();
void generateMaze(int x, int y);
bool hasWall(Position pos, int dx, int dy);