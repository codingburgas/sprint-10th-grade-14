#include "sizeSelect.h"
#include "config.h"
#include "utils.h" 
#include "button.h" 
GameState sizeSelection()
{
    int framesSinceStart = 0;
    const int COOLDOWN_FRAMES = 10;

    Texture2D background = LoadTexture("assets/background.png");

    int screenWidth = 1440;
    float centerX = screenWidth / 2 - 100;
    int buttonY = 350;

    Button smallButton{ "assets/smallbutton.png", Vector2(126.0f, buttonY), 0.25 };
    Button mediumButton{ "assets/mediumbutton.png", Vector2(564.0f, buttonY), 0.25 };
    Button largeButton{ "assets/largebutton.png", Vector2(1002.0f, buttonY), 0.25 };
    Button backButton{ "assets/backbutton.png", {595, 650}, 0.2 };

    Font fontTitle = LoadFontEx("fonts/CinzelDecorative-Black.ttf", 100, 0, 0);
    Color title = { 245, 210, 123, 255 };

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

        DrawTextEx(fontTitle, "Select Difficulty", (Vector2{ 215, 110 }), (float)fontTitle.baseSize, 15, title);

      
        smallButton.Draw();
        mediumButton.Draw();
        largeButton.Draw();
        backButton.Draw();

       
        char smallTime[50], mediumTime[50], largeTime[50];

        if (bestTimes[SMALL] > 0)
            sprintf(smallTime, "Best: %.2fs", bestTimes[SMALL]);
        else
            sprintf(smallTime, "No best time");

        if (bestTimes[MEDIUM] > 0)
            sprintf(mediumTime, "Best: %.2fs", bestTimes[MEDIUM]);
        else
            sprintf(mediumTime, "No best time");

        if (bestTimes[LARGE] > 0)
            sprintf(largeTime, "Best: %.2fs", bestTimes[LARGE]);
        else
            sprintf(largeTime, "No best time");

      
        DrawText(smallTime, 150, 500, 20, YELLOW);
        DrawText(mediumTime, 588, 500, 20, YELLOW);
        DrawText(largeTime, 1026, 500, 20, YELLOW);

        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
    return NIL;
}