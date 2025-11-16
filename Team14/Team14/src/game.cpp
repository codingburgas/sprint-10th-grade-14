#include "game.h"
#include "mazegeneration.h"
#include "walltexture.h"
#include "player.h"

bool gameWon = false;
Texture2D boyTexture;
Texture2D villageTexture;
Texture2D background;

void setupGame()
{
    boyTexture = LoadTexture("assets/boyimage.png");
    villageTexture = LoadTexture("assets/villageimage.png");
    background = LoadTexture("assets/background.png");

 
    loadWallTextures();

    initializeMaze();
    generateMaze(0, 0);
    player.x = 0;
    player.y = 0;
    goal.x = gridWidth - 1;
    goal.y = gridHeight - 1;
    gameWon = false;
}

void updateGame()
{
    if (gameWon) return;
    if (IsKeyPressed(KEY_RIGHT)) movePlayer(1, 0);
    if (IsKeyPressed(KEY_LEFT)) movePlayer(-1, 0);
    if (IsKeyPressed(KEY_UP)) movePlayer(0, -1);
    if (IsKeyPressed(KEY_DOWN)) movePlayer(0, 1);
    if (player.x == goal.x && player.y == goal.y) gameWon = true;
}

void drawGame()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(background, 0, 0, WHITE);
    DrawRectangle(0, 0, 1440, 850, { 0, 0, 0, 100 });

    if (gameWon)
    {
        DrawText("You win!", 1440 / 2 - MeasureText("You win!", 30) / 2, 800 / 2 - 15, 30, DARKGREEN);
    }
    else
    {
        int screenWidth = 1440;
        int screenHeight = 800;
        int mazeWidth = gridWidth * cellSize;
        int mazeHeight = gridHeight * cellSize;
        int offsetX = (screenWidth - mazeWidth) / 2;
        int offsetY = (screenHeight - mazeHeight+50) / 2;
        // --- NEW: Highlight goal cell ---
        int goalPosX = goal.x * cellSize + offsetX;
        int goalPosY = goal.y * cellSize + offsetY;
        DrawRectangle(goalPosX, goalPosY, cellSize, cellSize, { 0, 255, 0, 100 }); // semi-transparent green


      
       

        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
            {
                int posX = i * cellSize + offsetX;
                int posY = j * cellSize + offsetY;

                if (maze[i][j].topWall) {
                    Rectangle dest = { posX, posY, cellSize, 10 };
                    DrawTexturePro(wallHorizontal,
                        { 0, 0, (float)wallHorizontal.width, (float)wallHorizontal.height },
                        dest, { 0, 0 }, 0.0f, WHITE);
                }

                if (maze[i][j].leftWall) {
                    Rectangle dest = { posX, posY, 10, cellSize };
                    DrawTexturePro(wallVertical,
                        { 0, 0, (float)wallVertical.width, (float)wallVertical.height },
                        dest, { 0, 0 }, 0.0f, WHITE);
                }
            }
        }

        for (int j = 0; j < gridHeight; j++) {
            int posX = gridWidth * cellSize + offsetX;
            int posY = j * cellSize + offsetY;
            Rectangle dest = { posX - 10, posY, 10, cellSize };
            DrawTexturePro(wallVertical,
                { 0, 0, (float)wallVertical.width, (float)wallVertical.height },
                dest, { 0, 0 }, 0.0f, WHITE);
        }

        for (int i = 0; i < gridWidth; i++) {
            int posX = i * cellSize + offsetX;
            int posY = gridHeight * cellSize + offsetY;
            Rectangle dest = { posX, posY - 10, cellSize, 10 };
            DrawTexturePro(wallHorizontal,
                { 0, 0, (float)wallHorizontal.width, (float)wallHorizontal.height },
                dest, { 0, 0 }, 0.0f, WHITE);
        }

        for (int j = 0; j < gridHeight; j++) {
            int posX = gridWidth * cellSize + offsetX;
            int posY = j * cellSize + offsetY;
            Rectangle dest = { posX - 10, posY, 10, cellSize };
            DrawTexturePro(wallVertical,
                { 0, 0, (float)wallVertical.width, (float)wallVertical.height },
                dest, { 0, 0 }, 0.0f, WHITE);
        }

        for (int i = 0; i < gridWidth; i++) {
            int posX = i * cellSize + offsetX;
            int posY = gridHeight * cellSize + offsetY;
            Rectangle dest = { posX, posY - 10, cellSize, 10 };
            DrawTexturePro(wallHorizontal,
                { 0, 0, (float)wallHorizontal.width, (float)wallHorizontal.height },
                dest, { 0, 0 }, 0.0f, WHITE);
        }
        Rectangle src = { 0, 0, boyTexture.width, boyTexture.height };
        Rectangle dest = {
            player.x * cellSize + offsetX + 10,
            player.y * cellSize + offsetY + 10,
            cellSize - 20,
            cellSize - 20
        };
        Vector2 origin = { 0, 0 };

        DrawTexturePro(boyTexture, src, dest, origin, 0.0f, WHITE);

        Rectangle srcGoal = { 0, 0, villageTexture.width, villageTexture.height };
        Rectangle destGoal = {
            goal.x * cellSize + offsetX + 10,
            goal.y * cellSize + offsetY + 10,
            cellSize - 20,
            cellSize - 20
        };
        Vector2 originGoal = { 0, 0 };

        DrawTexturePro(villageTexture, srcGoal, destGoal, originGoal, 0.0f, WHITE); 
        // --- NEW: Debug overlay ---
        std::string debugText = "Player: (" + std::to_string(player.x) + ", " + std::to_string(player.y) + ")";
        debugText += " | FPS: " + std::to_string(GetFPS());
        DrawText(debugText.c_str(), 20, 20, 20, RAYWHITE);
        // --- NEW: Mini debug panel ---
        std::string mazeSizeText;
        switch (currentMazeSize) {
        case SMALL: mazeSizeText = "SMALL"; break;
        case MEDIUM: mazeSizeText = "MEDIUM"; break;
        case LARGE: mazeSizeText = "LARGE"; break;
        }

        int visitedCount = 0;
        for (int i = 0; i < gridWidth; i++) {
            for (int j = 0; j < gridHeight; j++) {
                if (maze[i][j].visited) visitedCount++;
            }
        }

        std::string debugPanel = "Maze Size: " + mazeSizeText + "\n";
        debugPanel += "Visited Cells: " + std::to_string(visitedCount);

        // Draw a small semi-transparent rectangle as background for panel
        DrawRectangle(20, 50, 200, 60, { 0, 0, 0, 150 });
        DrawText(debugPanel.c_str(), 25, 55, 18, YELLOW);


    }

    EndDrawing();
}

GameState game()
{
    setupGame();

    while (!WindowShouldClose())
    {
        updateGame();
        drawGame();

        if (IsKeyPressed(KEY_ESCAPE))
        {
            UnloadTexture(boyTexture);
            UnloadTexture(villageTexture);
            unloadWallTextures();  // Clean up wall textures
            return MENU;
        }
    }
    UnloadTexture(boyTexture);
    UnloadTexture(villageTexture);
    unloadWallTextures();  // Clean up wall textures
    return NIL;
}