#include "include/app.h"

int main()
{
	App* app = new App({ 1440, 800 }, "placeholder");
	app->Run();

	delete app;
}