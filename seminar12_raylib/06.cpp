#include "raylib.h"

int main() {
    int screenWidth = 800;
    int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "Mouse Hover");
    
    Rectangle rect = {screenWidth/2 - 100, screenHeight/2 - 50, 200, 100};
    
    Color rect_color = GREEN;
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, rect)) {rect_color = RED;}
        else {rect_color = GREEN;}
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleRec(rect, rect_color);
        EndDrawing();
    }
    CloseWindow();
}