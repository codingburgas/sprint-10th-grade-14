#pragma once
#include "utils.h"
#include "config.h"



extern Cell maze[41][41];
extern Position goal;

void generateCollectibles(int count);
void initializeMaze();
void generateMaze(int x, int y);
bool hasWall(Position pos, int dx, int dy);