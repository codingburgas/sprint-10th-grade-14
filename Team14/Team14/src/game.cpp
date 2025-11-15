#include "game.h"
#include "mazegeneration.h"
#include "player.h"

bool gameWon = false;

void setupGame()
{
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

      
        DrawRectangleLines(offsetX, offsetY, mazeWidth, mazeHeight, WHITE);

      
        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
            {
                int posX = i * cellSize + offsetX;
                int posY = j * cellSize + offsetY;

              
                if (j > 0 && maze[i][j].topWall)
                    DrawLine(posX, posY, posX + cellSize, posY, WHITE);

                
                if (i < gridWidth - 1 && maze[i][j].rightWall)
                    DrawLine(posX + cellSize, posY, posX + cellSize, posY + cellSize, WHITE);

                if (j < gridHeight - 1 && maze[i][j].bottomWall)
                    DrawLine(posX, posY + cellSize, posX + cellSize, posY + cellSize, WHITE);

              
                if (i > 0 && maze[i][j].leftWall)
                    DrawLine(posX, posY, posX, posY + cellSize, WHITE);
            }
        }

        DrawRectangle(
            player.x * cellSize + offsetX + 2,
            player.y * cellSize + offsetY + 2,
            cellSize - 4,
            cellSize - 4,
            BLUE
        );

        DrawRectangle(
            goal.x * cellSize + offsetX + 2,
            goal.y * cellSize + offsetY + 2,
            cellSize - 4,
            cellSize - 4,
            GREEN
        );
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
            break;
        }
    }

    return MENU;
}