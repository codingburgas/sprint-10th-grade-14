#include "mainMenu.h"

GameState mainMenu()
{

	Texture2D background = LoadTexture("assets/testbackground.jpg");


	while (!WindowShouldClose())
	{
		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);


		BeginDrawing();

		ClearBackground(RED);
		DrawTexture(background, 0, 0, WHITE);


		EndDrawing();
	}

	CloseWindow();
	return NIL;
}