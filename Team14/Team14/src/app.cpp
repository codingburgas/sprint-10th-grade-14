#include "app.h"
#include "mainMenu.h"
#include "sizeSelect.h"
#include "game.h"

App::App(Vector2 setScreen, std::string setName)
	: screen(setScreen), name(setName), gameState(MENU)
{
	InitWindow((int)screen.x, (int)screen.y, name.c_str());
	SetTargetFPS(60);
}
App::~App() {}

void App::Run()
{
	while (gameState != NIL)
	{
		PollInputEvents();

		switch (gameState)
		{
		case MENU:
			gameState = mainMenu();
			break;
		case SIZESELECT:
			gameState = sizeSelection();
			break;
		case GAME:
			gameState = game();
			break;
		}

		PollInputEvents();
	}
}