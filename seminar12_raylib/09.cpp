#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Circle {
    Vector2 center;
    float radius;
    Color color;
};

int main() {
    InitWindow(800, 800, "Circle Creator");
    vector<Circle> circles;
    float radius = 30.0f;
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {circles.push_back({mousePos, radius, WHITE});}
        
        if (IsKeyPressed(KEY_SPACE)) {
            for (Circle &c : circles) {
                Color newColor = (Color){(unsigned char)(GetRandomValue(0, 255)), (unsigned char)(GetRandomValue(0, 255)), (unsigned char)(GetRandomValue(0, 255)), (unsigned char)GetRandomValue(128, 255)};
                c.color = newColor;
            }
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        for (const Circle &c : circles) {DrawCircleV(c.center, c.radius, c.color);}
        EndDrawing();
    }
    CloseWindow();
}