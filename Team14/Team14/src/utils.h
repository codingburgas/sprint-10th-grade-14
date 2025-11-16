#pragma once

#include <raylib.h>
#include <string>


class Button;

enum GameState {
    MENU = 0,
    STORY,
    SIZESELECT,
    GAME,
    NIL
};

struct TimerData {
    float currentTime;
    float bestTime;
    bool timerRunning;
};