#include "raylib.h"

int main(void) {
    const int screenWidth = 400;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Hello");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
