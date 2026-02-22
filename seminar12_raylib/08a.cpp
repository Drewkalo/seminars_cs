#include "raylib.h"
#include <math.h>

int main() {
    int screenWidth = 800;
    int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "Attraction to Mouse - A");
    
    Vector2 circle_pos = {400.0f, 400.0f};
    float circle_radius = 30.0f;
    float speed = 10.0f;
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        Vector2 mouse_pos = GetMousePosition();
        
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 direction = {mouse_pos.x - circle_pos.x, mouse_pos.y - circle_pos.y};
            float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
            Vector2 normalized_direction = {direction.x / distance, direction.y / distance};
    
            circle_pos.x += normalized_direction.x * speed;
            circle_pos.y += normalized_direction.y * speed;
            if (distance < speed) {circle_pos = mouse_pos;}
        }
       
        if (circle_pos.x < circle_radius) {
            circle_pos.x = circle_radius;
        }
        if (circle_pos.x > screenWidth - circle_radius) {
            circle_pos.x = screenWidth - circle_radius;
        }
        if (circle_pos.y < circle_radius) {
            circle_pos.y = circle_radius;
        }
        if (circle_pos.y > screenHeight - circle_radius) {
            circle_pos.y = screenHeight - circle_radius;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(circle_pos, circle_radius, RED);
        EndDrawing();
    }
    CloseWindow();
}