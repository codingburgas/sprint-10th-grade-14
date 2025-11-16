#pragma once
#include "utils.h"
#include "mazegeneration.h"
#include "player.h"
#include "walltexture.h"

extern bool gameWon;
extern TimerData timer; 

void setupGame();
void updateGame();
void drawGame();
GameState game();


void startTimer();
void stopTimer();
void updateTimer();
void drawTimer();
void saveBestTime();
void loadBestTimes();