#pragma once

#include "utils.h"
#include "config.h"

void initializeMaze();
void generateMaze(int x, int y);
void drawMaze();
void drawGoal();
bool hasWall(Position pos, int dx, int dy);