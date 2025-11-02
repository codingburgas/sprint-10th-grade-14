#include "app.h"
#include "mainMenu.h"

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
		switch (gameState)
		{
		case MENU: gameState = mainMenu();
			break;
		}
	}
}