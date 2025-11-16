#pragma once
#include "utils.h"
#include "config.h"

// Remove the Cell struct definition here since it's in config.h
// Just declare the maze array and functions

extern Cell maze[41][41];
extern Position goal;

void initializeMaze();
void generateMaze(int x, int y);
bool hasWall(Position pos, int dx, int dy);