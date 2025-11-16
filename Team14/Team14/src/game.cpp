#include "game.h"
#include "mazegeneration.h"
#include "walltexture.h"
#include "player.h"
#include "config.h"
#include <cstdio>  // For sprintf

bool gameWon = false;
Texture2D boyTexture;
Texture2D villageTexture;
Texture2D background;

TimerData timer = { 0.0f, 0.0f, false };

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

    loadBestTimes();
    timer.currentTime = 0.0f;
    timer.bestTime = bestTimes[currentMazeSize];
    timer.timerRunning = true;
}

void updateGame()
{
    if (gameWon) return;

    if (timer.timerRunning) {
        updateTimer();
    }

    if (IsKeyPressed(KEY_RIGHT)) movePlayer(1, 0);
    if (IsKeyPressed(KEY_LEFT)) movePlayer(-1, 0);
    if (IsKeyPressed(KEY_UP)) movePlayer(0, -1);
    if (IsKeyPressed(KEY_DOWN)) movePlayer(0, 1);

    if (player.x == goal.x && player.y == goal.y) {
        gameWon = true;
        stopTimer();
        saveBestTime();
    }
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

        char timeText[100];
        sprintf(timeText, "Time: %.2f seconds", timer.currentTime);
        DrawText(timeText, 1440 / 2 - MeasureText(timeText, 25) / 2, 800 / 2 + 30, 25, WHITE);

        if (timer.bestTime > 0) {
            char bestTimeText[100];
            sprintf(bestTimeText, "Best: %.2f seconds", timer.bestTime);
            DrawText(bestTimeText, 1440 / 2 - MeasureText(bestTimeText, 25) / 2, 800 / 2 + 70, 25, YELLOW);
        }
        else {
            DrawText("New Best Time!", 1440 / 2 - MeasureText("New Best Time!", 25) / 2, 800 / 2 + 70, 25, GOLD);
        }
    }
    else
    {
        int screenWidth = 1440;
        int screenHeight = 800;
        int mazeWidth = gridWidth * cellSize;
        int mazeHeight = gridHeight * cellSize;
        int offsetX = (screenWidth - mazeWidth) / 2;
        int offsetY = (screenHeight - mazeHeight + 50) / 2;
        // --- NEW: Highlight goal cell ---
        int goalPosX = goal.x * cellSize + offsetX;
        int goalPosY = goal.y * cellSize + offsetY;
        DrawRectangle(goalPosX, goalPosY, cellSize, cellSize, { 0, 255, 0, 100 }); // semi-transparent green
        drawTimer();

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

        DrawTexturePro(villageTexture, srcGoal, destGoal, originGoal, 0.0f, WHITE);
        // --- NEW: Debug overlay ---
        std::string debugText = "Player: (" + std::to_string(player.x) + ", " + std::to_string(player.y) + ")";
        debugText += " | FPS: " + std::to_string(GetFPS());
        DrawText(debugText.c_str(), 20, 20, 20, RAYWHITE);

    }

    EndDrawing();
}

void startTimer() {
    timer.timerRunning = true;
    timer.currentTime = 0.0f;
}

void stopTimer() {
    timer.timerRunning = false;
}

void updateTimer() {
    if (timer.timerRunning) {
        timer.currentTime += GetFrameTime();
    }
}

void drawTimer() {
    char timerText[50];
    sprintf(timerText, "Time: %.2f", timer.currentTime);

    // Position timer in top-right corner to avoid maze overlap
    int textWidth = MeasureText(timerText, 30);
    DrawText(timerText, 1440 - textWidth - 20, 20, 30, WHITE);

    if (timer.bestTime > 0) {
        char bestText[50];
        sprintf(bestText, "Best: %.2f", timer.bestTime);
        int bestTextWidth = MeasureText(bestText, 25);
        DrawText(bestText, 1440 - bestTextWidth - 20, 60, 25, YELLOW);
    }
}

void saveBestTime() {
    if (timer.bestTime == 0 || timer.currentTime < timer.bestTime) {
        bestTimes[currentMazeSize] = timer.currentTime;
        timer.bestTime = timer.currentTime;
        saveBestTimesToFile(); 
    }
}

void loadBestTimes() {
    loadBestTimesFromFile();  // Load from file at game start
}

void resetTimer() {
    timer.currentTime = 0.0f;
    timer.timerRunning = true;
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
            unloadWallTextures();
            return MENU;
        }

        // Optional: Add restart functionality with R key
        if (IsKeyPressed(KEY_R)) {
            resetTimer();
            setupGame();
        }
    }
    UnloadTexture(boyTexture);
    UnloadTexture(villageTexture);
    unloadWallTextures();
    return NIL;
}