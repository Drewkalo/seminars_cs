#include "raylib.h"
#include <string>
#include <iostream>

int main() {
    int screenWidth = 800;
    int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "Mouse Coordinates");
    
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Vector2 mouse_position = GetMousePosition();
        
        std::string x_text = "X: " + std::to_string((int)mouse_position.x);
        std::string y_text = "Y: " + std::to_string((int)mouse_position.y);
        std::string full = "Mouse Position: (" + x_text + ", " + y_text + ")";
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
    
        DrawText(x_text.c_str(), 50, 50, 30, DARKGRAY);
        DrawText(y_text.c_str(), 50, 100, 30, DARKGRAY);
        DrawText(full.c_str(), 50, 200, 30, MAROON);
        EndDrawing();
    }
    CloseWindow();
}