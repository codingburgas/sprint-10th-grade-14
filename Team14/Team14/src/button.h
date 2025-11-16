#pragma once
#include <raylib.h>

class Button
{
public:
    Button(const char* imagePath, Vector2 imagePosition, float scale);
    ~Button();

    void Draw();
    bool isPressed(Vector2 mousePos, bool mousePressed);

   
    int getWidth() const { return texture.width; }
    int getHeight() const { return texture.height; }
    Vector2 getPosition() const { return position; }
    Rectangle getRect() const { return { position.x, position.y, (float)texture.width, (float)texture.height }; }

private:
    Texture2D texture;
    Vector2 position;
};