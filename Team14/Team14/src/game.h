#pragma once
#include "utils.h"
#include "mazegeneration.h"
#include "player.h"
#include "walltexture.h"  // Add this

extern bool gameWon;

void setupGame();
void updateGame();
void drawGame();
GameState game();