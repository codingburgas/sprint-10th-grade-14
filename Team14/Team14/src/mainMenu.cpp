#include "mainMenu.h"
#include "sizeSelect.h" 

GameState mainMenu()
{
    Texture2D background = LoadTexture("assets/background.png");

    const int screenWidth = 1440;
    float centerX = screenWidth / 2 - 100;

    Button playButton{ "assets/playbutton.png", {centerX, 300}, 0.175 };
    Button storyButton{ "assets/storybutton.png", {centerX, 450}, 0.175 };
    Button quitButton{ "assets/quitbutton.png", {centerX, 600}, 0.175 };
    Font fontTitle = LoadFontEx("fonts/CinzelDecorative-Black.ttf", 128, 0, 0);
    Color title = { 245, 210, 123, 255 };

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
            UnloadTexture(background);
            return STORY;
        }
        if (quitButton.isPressed(mousePosition, mousePressed))
        {
            break;
        }

        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);
        DrawRectangle(0, 0, 1440, 800, { 0, 0, 0, 100 });

        DrawTextEx(fontTitle, "The Lost Way", (Vector2{ 300, 110 }), (float)fontTitle.baseSize, 15, title);

        playButton.Draw();
        storyButton.Draw();
        quitButton.Draw();

        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
    return NIL;
}