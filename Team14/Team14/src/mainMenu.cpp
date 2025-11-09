#include "mainMenu.h"
#include "sizeSelect.h" 

GameState mainMenu()
{
    Texture2D background = LoadTexture("assets/background.png");

    int screenWidth = 1440;
    float centerX = screenWidth / 2 - 100;

    Button playButton{ "assets/playbutton.png", {centerX, 300}, 0.175 };
    Button storyButton{ "assets/storybutton.png", {centerX, 450}, 0.175 };
    Button quitButton{ "assets/quitbutton.png", {centerX, 600}, 0.175 };

    while (!WindowShouldClose())
    {
        BeginDrawing();

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (playButton.isPressed(mousePosition, mousePressed))
        {
            UnloadTexture(background);
            return SIZESELECT;
        }
        if (storyButton.isPressed(mousePosition, mousePressed))
        {
        }
        if (quitButton.isPressed(mousePosition, mousePressed))
        {
            break;
        }

        ClearBackground(BLACK);

        if (background.id != 0) {
            DrawTexture(background, 0, 0, WHITE);
        }

        DrawText("MAZE GAME", screenWidth / 2 - MeasureText("MAZE GAME", 60) / 2, 100, 60, WHITE);

        playButton.Draw();
        storyButton.Draw();
        quitButton.Draw();

        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
    return NIL;
}