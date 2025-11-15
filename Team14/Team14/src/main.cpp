#include "app.h"

int main()
{
	App* app = new App({ 1440, 850 }, "The Lost Way");
	app->Run();

	delete app;
}