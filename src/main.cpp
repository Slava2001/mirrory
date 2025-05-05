#include "raylib.h"
#include "level.h"

int main(void) {
    const int screenWidth = 400;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Hello");

    SetTargetFPS(60);

    Level lvl;

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            lvl.update();
            lvl.draw();
            DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
