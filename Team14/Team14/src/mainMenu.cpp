#include "mainMenu.h"
#include <iostream>

GameState mainMenu()
{

	Texture2D background = LoadTexture("assets/background.png");
	Button playButton{ "assets/playbutton.png", {600, 300}, 0.175 };
	Button storyButton{ "assets/storybutton.png", {600, 450}, 0.175 };
	Button quitButton{ "assets/playbutton.png", {600, 600}, 0.175 };


	while (!WindowShouldClose())
	{
		BeginDrawing();

		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

		if (playButton.isPressed(mousePosition, mousePressed))
		{
			UnloadTexture(background);
			return GAME;
		}
		if (quitButton.isPressed(mousePosition, mousePressed))
		{
			break;
		}
		
		ClearBackground(BLACK);
		DrawTexture(background, 0, 0, WHITE);
		playButton.Draw();
		storyButton.Draw();
		quitButton.Draw();

		EndDrawing();
	}

	CloseWindow();
	return NIL;
}