#include "game.h"

extern Position player;
extern Position goal; 
bool gameWon = false;

void setupGame()
{
	initializeMaze();
	generateMaze(0, 0);
	player.x = 0;
	player.y = 0;
	goal.x = gridWidth - 1;
	goal.y = gridHeight - 1;
	gameWon = false;
}

void updateGame()
{
	if (gameWon) return;
	if (IsKeyPressed(KEY_RIGHT)) movePlayer(1, 0);
	if (IsKeyPressed(KEY_LEFT)) movePlayer(-1, 0);
	if (IsKeyPressed(KEY_UP)) movePlayer(0, -1);
	if (IsKeyPressed(KEY_DOWN)) movePlayer(0, 1);
	if (player.x == goal.x && player.y == goal.y) gameWon = true;
}

void drawGame()
{
	BeginDrawing();
	ClearBackground(BLACK);

	if (gameWon)
	{
		DrawText("You win!", 1440 / 2 - 50, 800 / 2, 30, DARKGREEN);
	}
	else
	{
		drawMaze();
		drawPlayer();
		drawGoal();
	}

	EndDrawing();
}

GameState game()
{
	setupGame();

	while (!WindowShouldClose())
	{
		updateGame();
		drawGame();
	}

	CloseWindow();
	return NIL;
}