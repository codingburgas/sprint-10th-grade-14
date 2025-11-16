#include "walltexture.h"


Texture2D wallHorizontal;
Texture2D wallVertical;

void loadWallTextures()
{
    wallHorizontal = LoadTexture("assets/wall-horizontal.png");
    wallVertical = LoadTexture("assets/wall-vertical.png");
}

void unloadWallTextures()
{
    UnloadTexture(wallHorizontal);
    UnloadTexture(wallVertical);
}