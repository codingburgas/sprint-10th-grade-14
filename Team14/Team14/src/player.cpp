#include "player.h"


Position player;

void drawPlayer()
{
    DrawRectangle(player.x * cellSize + 10, player.y * cellSize + 10,
        cellSize - 20, cellSize - 20, BLUE);
}

void movePlayer(int dx, int dy)
{
    int newX = player.x + dx;
    int newY = player.y + dy;

    if (newX < 0 || newX >= gridWidth || newY < 0 || newY >= gridHeight) return;
    if (hasWall(player, dx, dy)) return;

    player.x = newX;
    player.y = newY;
}