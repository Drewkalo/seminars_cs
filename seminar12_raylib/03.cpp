#include "raylib.h"
#include <math.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "Rotating square");
    
    float size = 200.0;
    Vector2 point = {400.0, 400.0};
    float angle = 0.0;
    const float rot_speed = 2.0;
    
    // вершины относительно точки вращения
    Vector2 vertices[4] = {
        {0.0, 0.0},
        {size, 0.0},
        {size, size},
        {0.0, size}
    };
    
    SetTargetFPS(60);
    
    // буду рисовать квадрат по сторонам, поворачивая каждую точку. Стороны (0,1) (1,2) (2,3) (3,0) точки
    while (!WindowShouldClose())
    {
        angle += rot_speed;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        for (int i = 0; i < 4; i++) {
            int next_index = (i + 1) % 4;
            
            Vector2 p1 = {
                point.x + vertices[i].x * cos(DEG2RAD *angle) - 
                                vertices[i].y * sin(DEG2RAD * angle),
                point.y + vertices[i].x * sin(DEG2RAD * angle) + 
                                vertices[i].y * cos(DEG2RAD * angle)
            };
            
            Vector2 p2 = {
                point.x + vertices[next_index].x * cos(DEG2RAD * angle) - 
                                vertices[next_index].y * sin(DEG2RAD * angle),
                point.y + vertices[next_index].x * sin(DEG2RAD * angle) + 
                                vertices[next_index].y * cos(DEG2RAD * angle)
            };
            
            DrawLineV(p1, p2, GREEN);
        }
        EndDrawing();
    }
    CloseWindow();
}