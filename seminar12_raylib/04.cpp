#include "raylib.h"
#include <math.h>
#include <iostream>

int main() {
    int screenWidth = 800;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Moving Circle");

    float angle = 0.0;
    float rot_speed = 1;
    const float radius = 50.0;
    Vector2 center = {400.0, 400.0};
    float orbitRadius = 200.0;
    float circleX, circleY;
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        angle += rot_speed;
        if (angle >= 360) {angle -= 360;}
        circleX = center.x + orbitRadius * sin(DEG2RAD * angle);
        circleY = center.y + orbitRadius * cos(DEG2RAD * angle);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(circleX, circleY, radius, GREEN);
        EndDrawing();
    }
    CloseWindow();
}