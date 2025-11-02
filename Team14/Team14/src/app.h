#pragma once

#include "utils.h"

class App {
public:
	App(Vector2 screenSize, std::string windowName);
	~App();

	void Run();

private:
	GameState gameState;
	Vector2 screen;
	std::string name;
};