#include "story.h"
#include <vector>
#include <string>
using namespace std;

const int screenWidth = 1440;
const int screenHeight = 850;

struct Story {
    vector<string> pages;
    int currentPage = 0;

    float charsShown = 0.0f;    // float for smooth typing
    float fadeAlpha = 0.0f;

    float shadowX = -300.0f;

    float typeSpeed = 50.0f;

    Texture2D background;
};

void ResetTextEffects(Story& story) {
    story.charsShown = 0;
    story.fadeAlpha = 0.0f;
}


void DrawShadow(const Story& story, int screenHeight) {
    DrawEllipse(story.shadowX, screenHeight /2, 200, 420, { 0,0,0,35 });
}

void DrawStoryText(const Story& story) {
    const string txt = story.pages[story.currentPage];
    Vector2 pos = { 50, 120 };

    int fontSize = 26;
    float spacing = 8.0f;

    DrawTextEx(GetFontDefault(), TextSubtext(txt.c_str(), 0, (int)story.charsShown), pos, fontSize, spacing, { 255, 240, 200, (unsigned char)story.fadeAlpha });
}

void HandleStoryInput(Story& story) {
    if (IsKeyPressed(KEY_RIGHT)) {
        if (story.currentPage < (int)story.pages.size() - 1) {
            story.currentPage++;
            ResetTextEffects(story);
        }
    }
    if (IsKeyPressed(KEY_LEFT)) {
        if (story.currentPage > 0) {
            story.currentPage--;
            ResetTextEffects(story);
        }
    }
}

void UpdateStory(Story& story, int screenWidth) {
    HandleStoryInput(story);

    // Shadow
    story.shadowX += 0.4f;
    if (story.shadowX > screenWidth + 200) story.shadowX = -300;

    // Fade
    story.fadeAlpha = min(story.fadeAlpha + 255 * GetFrameTime(), 255.0f);

    // Typing
    story.charsShown += story.typeSpeed * GetFrameTime();
    story.charsShown = min(story.charsShown, (float)story.pages[story.currentPage].length());
}

void DrawStoryScreen(const Story& story, int screenWidth, int screenHeight) {
    DrawTexture(story.background, 0, 0, WHITE);
    DrawRectangle(0, 0, screenWidth, screenHeight, { 0,0,0,150 });
    DrawShadow(story, screenHeight);
    DrawStoryText(story);

    DrawText("<- Back | Next ->", 50, screenHeight - 90, 20, { 200,200,200,180 });
    DrawText("Press BACKSPACE to return", 50, screenHeight - 50, 20, { 200,200,200,140 });
}

GameState story() {

    Story s;

    s.pages = {
        "Long ago, the village slept peacefully at the edge of the forest,\n"
        "\nwhere every shadow told a story and every rustle carried a warning.\n"
        "\nNow, the boy finds himself lost among towering trees and tangled paths,\n"
        "\nchasing the faint glimmer of home.",

        "Legends speak of wandering spirits that guard the forest’s secrets.\n"
        "\nSome say the roots themselves shift to confuse those who stray.\n"
        "\n"
        "\nBut one truth remains:\n"
        "\nevery step deeper changes the traveler forever.",

        "\nTonight, the wind carries whispers of a path unseen.\n"
        "\nAnd the forest watches, patient and waiting, as you take your first step."
    };

    s.background = LoadTexture("assets/background.png");

    while (!WindowShouldClose()) {
        UpdateStory(s, screenWidth);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawStoryScreen(s, screenWidth, screenHeight);
        EndDrawing();

        if (IsKeyPressed(KEY_BACKSPACE)) return MENU;
    }

    UnloadTexture(s.background);

    return NIL;
}