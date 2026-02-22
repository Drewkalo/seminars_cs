#include "raylib.h"

int main() {
    int screenWidth = 800;
    int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "Mouse Hover");
    
    float velocity = 10.0;
    Vector2 circle_pos = {400.0, 400.0};
    Color circle_color = GREEN;
    float circle_radius = 50.0;
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) {circle_pos.x += velocity;}
        if (IsKeyDown(KEY_LEFT)) {circle_pos.x -= velocity;}
        if (IsKeyDown(KEY_UP)) {circle_pos.y -= velocity;}
        if (IsKeyDown(KEY_DOWN)) {circle_pos.y += velocity;}
        if (IsKeyPressed(KEY_SPACE)) {circle_color = (Color){(unsigned char)(GetRandomValue(0, 255)), (unsigned char)(GetRandomValue(0, 255)), (unsigned char)(GetRandomValue(0, 255)), (unsigned char)GetRandomValue(128, 255)};}

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(circle_pos, circle_radius, circle_color);
        EndDrawing();
    }
    CloseWindow();
}