#include "mazegeneration.h"
#include "config.h"

struct Cell
{
	bool visited;
	bool topWall, bottomWall, leftWall, rightWall;
};

Cell maze[gridWidth][gridHeight];
Position goal;


void initializeMaze()
{
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			maze[i][j].visited = false;
			maze[i][j].topWall = true;
			maze[i][j].bottomWall = true;
			maze[i][j].leftWall = true;
			maze[i][j].rightWall = true;
		}
	}
}

void generateMaze(int x, int y)
{
	maze[x][y].visited = true;
	while (true)
	{
		int directions[] = { 0, 1, 2, 3 }; // up, right, down, left
		for (int i = 0; i < 4; i++)
		{
			int j = GetRandomValue(i, 3);
			int temp = directions[i];
			directions[i] = directions[j];
			directions[j] = temp;
		}
		bool moved = false;
		for (int i = 0; i < 4; i++)
		{
			int nx = x, ny = y;
			switch (directions[i])
			{
			case 0: ny -= 1; // up
				break;
			case 1: nx += 1; // right
				break;
			case 2: ny += 1; // down
				break;
			case 3: nx -= 1; // left
				break;
			}

			if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight && !maze[nx][ny].visited)
			{
				if (directions[i] == 0)
				{
					maze[x][y].topWall = false;
					maze[nx][ny].bottomWall = false;
				} else if (directions[i] == 1) {
					maze[x][y].rightWall = false;
					maze[nx][ny].leftWall = false;
				} else if (directions[i] == 2) {
					maze[x][y].bottomWall = false;
					maze[nx][ny].topWall = false;
				} else if (directions[i] == 3) {
					maze[x][y].leftWall = false;
					maze[nx][ny].rightWall = false;
				}

				generateMaze(nx, ny);
				moved = true;
				break;
			}
		}
		if (!moved) break;
	}
}

void drawMaze()
{
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			int posX = i * cellSize;
			int posY = j * cellSize;
			if (maze[i][j].topWall) DrawLine(posX, posY, posX + cellSize, posY, WHITE);
			if (maze[i][j].rightWall) DrawLine(posX + cellSize, posY, posX + cellSize, posY + cellSize, WHITE);
			if (maze[i][j].bottomWall) DrawLine(posX, posY + cellSize, posX + cellSize, posY + cellSize, WHITE);
			if (maze[i][j].leftWall) DrawLine(posX, posY, posX, posY + cellSize, WHITE);
		}
	}
}

void drawGoal()
{
	DrawRectangle(goal.x * cellSize + 2, goal.y * cellSize + 2, cellSize - 4, cellSize - 4, GREEN);
}

bool hasWall(Position pos, int dx, int dy)
{
	Cell& cell = maze[pos.x][pos.y];

	if (dx == -1) return cell.leftWall;
	if (dx == 1)  return cell.rightWall;
	if (dy == -1) return cell.topWall;
	if (dy == 1)  return cell.bottomWall;

	return false;
}