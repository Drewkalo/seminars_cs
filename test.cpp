#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

struct Ball {
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    float mass;
    float charge;
    float radius;
    Color color;
};

const float DT = 0.01f;
const float COULOMB_CONST = 200.0f;
const float MIN_DISTANCE = 20.0f;
const float MAX_SPEED = 500.0f;

float RandomFloat(float min, float max) {
    return min + (float)rand() / RAND_MAX * (max - min);
}

Color GetColorFromCharge(float charge) {
    if (charge > 0) {
        unsigned char intensity = (unsigned char)min(255.0f, 150.0f + abs(charge) * 50);
        return (Color){intensity, 50, 50, 255};
    } else {
        unsigned char intensity = (unsigned char)min(255.0f, 150.0f + abs(charge) * 50);
        return (Color){50, 50, intensity, 255};
    }
}

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    
    InitWindow(screenWidth, screenHeight, "N-Body Simulation - Coulomb Force");
    
    srand(time(NULL));
    vector<Ball> balls;
    
    float accumulator = 0.0f;
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        float frameTime = GetFrameTime();
        Vector2 mousePos = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // ЛКМ - маленькая масса, отрицательный заряд
            Ball newBall;
            newBall.pos = mousePos;
            newBall.vel = {0, 0};
            newBall.acc = {0, 0};
            newBall.mass = RandomFloat(0.5f, 2.0f);
            newBall.charge = RandomFloat(-3.0f, -1.0f);
            newBall.radius = 10.0f + newBall.mass * 2;
            newBall.color = GetColorFromCharge(newBall.charge);
            balls.push_back(newBall);
        }
        
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            Ball newBall;
            newBall.pos = mousePos;
            newBall.vel = {0, 0};
            newBall.acc = {0, 0};
            newBall.mass = RandomFloat(8.0f, 15.0f);
            newBall.charge = RandomFloat(1.0f, 5.0f);
            newBall.radius = 10.0f + newBall.mass * 2;
            newBall.color = GetColorFromCharge(newBall.charge);
            balls.push_back(newBall);
        }
        accumulator += frameTime;
        int maxSteps = 10;
        int stepCount = 0;
        
        while (accumulator >= DT && stepCount < maxSteps) {
            for (size_t i = 0; i < balls.size(); i++) {
                balls[i].acc = {0, 0};
                for (size_t j = 0; j < balls.size(); j++) {
                    if (i == j) continue;
                    Vector2 diff = {
                        balls[j].pos.x - balls[i].pos.x,
                        balls[j].pos.y - balls[i].pos.y
                    };
                    
                    float distance = sqrt(diff.x * diff.x + diff.y * diff.y);
                    
                    if (distance < MIN_DISTANCE) {
                        continue;
                    }
                    
                    float forceMagnitude = COULOMB_CONST * 
                                          balls[i].charge * balls[j].charge / distance;
                    
                    Vector2 forceDir = {-diff.x / distance, -diff.y / distance};
                    
                    balls[i].acc.x += forceMagnitude * forceDir.x / balls[i].mass;
                    balls[i].acc.y += forceMagnitude * forceDir.y / balls[i].mass;
                }
            }
            
            for (Ball &ball : balls) {
                ball.vel.x += ball.acc.x * DT;
                ball.vel.y += ball.acc.y * DT;
                
                ball.pos.x += ball.vel.x * DT;
                ball.pos.y += ball.vel.y * DT;
                
                if (ball.pos.x < ball.radius) {
                    ball.pos.x = ball.radius;
                    ball.vel.x = -ball.vel.x;
                }
                if (ball.pos.x > screenWidth - ball.radius) {
                    ball.pos.x = screenWidth - ball.radius;
                    ball.vel.x = -ball.vel.x;
                }
                if (ball.pos.y < ball.radius) {
                    ball.pos.y = ball.radius;
                    ball.vel.y = -ball.vel.y;
                }
                if (ball.pos.y > screenHeight - ball.radius) {
                    ball.pos.y = screenHeight - ball.radius;
                    ball.vel.y = -ball.vel.y;
                }
            }
            
            accumulator -= DT;
            stepCount++;
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        for (const Ball &ball : balls) {DrawCircleV(ball.pos, ball.radius, ball.color);}
        EndDrawing();
    }
    CloseWindow();
}