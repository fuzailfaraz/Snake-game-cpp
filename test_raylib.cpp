#include "raylib.h"
#include "Snake.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int cellSize = 20;

    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(60);

    Snake snake(screenWidth / cellSize / 2, screenHeight / cellSize / 2);

    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();

        if (IsKeyPressed(KEY_UP)) snake.SetDirection({0, -1});
        if (IsKeyPressed(KEY_DOWN)) snake.SetDirection({0, 1});
        if (IsKeyPressed(KEY_LEFT)) snake.SetDirection({-1, 0});
        if (IsKeyPressed(KEY_RIGHT)) snake.SetDirection({1, 0});

        snake.Update(deltaTime);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        snake.Draw(cellSize);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
