#include "game.h"

Color green = { 173,204,96,255 };

GameState game()
{
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(green);


		EndDrawing();
	}

	CloseWindow();
	return NIL;
}