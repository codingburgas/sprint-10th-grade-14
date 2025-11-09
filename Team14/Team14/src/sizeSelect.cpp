#include "sizeSelect.h"
#include "config.h"

GameState sizeSelection()
{
    int framesSinceStart = 0;
    const int COOLDOWN_FRAMES = 10;

    Texture2D background = LoadTexture("assets/background.png");

    int screenWidth = 1440;
    float centerX = screenWidth / 2 - 100;

    Button smallButton{ "assets/smallbutton.png", {centerX, 150}, 0.175 };
    Button mediumButton{ "assets/mediumbutton.png", {centerX, 325}, 0.175 };
    Button largeButton{ "assets/largebutton.png", {centerX, 500}, 0.175 };
    Button backButton{ "assets/backbutton.png", {centerX, 675}, 0.175 };

    while (!WindowShouldClose())
    {
        BeginDrawing();

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        bool canClick = (framesSinceStart > COOLDOWN_FRAMES);
        framesSinceStart++;

        if (canClick && smallButton.isPressed(mousePosition, mousePressed))
        {
            setMazeSize(SMALL);
            UnloadTexture(background);
            return GAME;
        }
        if (canClick && mediumButton.isPressed(mousePosition, mousePressed))
        {
            setMazeSize(MEDIUM);
            UnloadTexture(background);
            return GAME;
        }
        if (canClick && largeButton.isPressed(mousePosition, mousePressed))
        {
            setMazeSize(LARGE);
            UnloadTexture(background);
            return GAME;
        }
        if (canClick && backButton.isPressed(mousePosition, mousePressed))
        {
            UnloadTexture(background);
            return MENU;
        }

        ClearBackground(BLACK);

        if (background.id != 0) {
            DrawTexture(background, 0, 0, WHITE);
        }

        DrawText("SELECT MAZE SIZE", screenWidth / 2 - MeasureText("SELECT MAZE SIZE", 60) / 2, 50, 60, YELLOW);

        smallButton.Draw();
        mediumButton.Draw();
        largeButton.Draw();
        backButton.Draw();

        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
    return NIL;
}