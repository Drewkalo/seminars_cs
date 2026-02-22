#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "Moving Circle");
    
    float circleX = 0;
    const float circleY = screenHeight / 2.0;
    const float circleRadius = 200.0;
    const float speed = 10.0;
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        circleX += speed;
        
        if (circleX - circleRadius > screenWidth) {circleX = -circleRadius;}
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawCircle(circleX, circleY, circleRadius, GREEN);
    
        EndDrawing();
    }
    CloseWindow();
}