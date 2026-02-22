#include "raylib.h"
#include <math.h>

int main() {
    int screenWidth = 800;
    int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "Attraction to Mouse - B");
    
    Vector2 circle_pos = {400.0f, 400.0f};
    Vector2 velocity = {0.0f, 0.0f};
    float circle_radius = 30.0f;
    float acceleration = 0.5f;
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        Vector2 mouse_pos = GetMousePosition();
        
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 direction = {mouse_pos.x - circle_pos.x, mouse_pos.y - circle_pos.y};
            float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
            
            Vector2 normalized_direction = {direction.x / distance, direction.y / distance};
            velocity.x += normalized_direction.x * acceleration;
            velocity.y += normalized_direction.y * acceleration;    
        }

        circle_pos.x += velocity.x;
        circle_pos.y += velocity.y;
        
       
        if (circle_pos.x < circle_radius) {
            circle_pos.x = circle_radius;
            velocity.x = -velocity.x;
        }
        if (circle_pos.x > screenWidth - circle_radius) {
            circle_pos.x = screenWidth - circle_radius;
            velocity.x = -velocity.x;
        }
        if (circle_pos.y < circle_radius) {
            circle_pos.y = circle_radius;
            velocity.y = -velocity.y;
        }
        if (circle_pos.y > screenHeight - circle_radius) {
            circle_pos.y = screenHeight - circle_radius;
            velocity.y = -velocity.y;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(circle_pos, circle_radius, RED);
        EndDrawing();
    }
    CloseWindow();
}