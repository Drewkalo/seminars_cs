#include "raylib.h"
#include <vector>

class Toggle {
private:
    Rectangle bounds;
    bool state;
    Color colorOn;
    Color colorOff;
    Color borderColor;
    
public:
    Toggle(float x, float y, float width, float height) : bounds{x, y, width, height}, state{false}, colorOn{GREEN}
    , colorOff{GRAY}, borderColor{DARKGRAY} {}
    
    void update() {
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {state = !state;}
    }
    
    void draw() {
    Color currentColor = state ? colorOn : colorOff;
    
    DrawRectangleRec(bounds, currentColor);
    DrawRectangleLinesEx(bounds, 2, borderColor);
    
    float knobWidth = bounds.height * 0.8f;
    float knobHeight = bounds.height * 0.8f;
    float knobY = bounds.y + (bounds.height - knobHeight) / 2;
    
    if (state) {
        float knobX = bounds.x + bounds.width - knobWidth - 5;
        DrawCircle(knobX + knobWidth/2, knobY + knobHeight/2, knobWidth/2, WHITE);
    } else {
        float knobX = bounds.x + 5;
        DrawCircle(knobX + knobWidth/2, knobY + knobHeight/2, knobWidth/2, WHITE);
    }
    
    const char* statusText = state ? "ON" : "OFF";
    int fontSize = bounds.height * 0.4f;
    
    int textWidth = MeasureText(statusText, fontSize);
    float textX = bounds.x + (bounds.width - textWidth) / 2;
    
    float textY = bounds.y + (bounds.height - fontSize) / 2;
    
    DrawText(statusText, textX, textY, fontSize, state ? DARKGREEN : DARKGRAY);
    }
    
    bool GetState() const {
        return state;
    }
    void SetPosition(float x, float y) {
        bounds.x = x;
        bounds.y = y;
    }
};

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Toggle Switches (10 switches)");
    
    SetTargetFPS(60);
    
    std::vector<Toggle> toggles;
    
    float toggleWidth = 120;
    float toggleHeight = 50;
    float startX = 50;
    float startY = 50;
    float verticalSpacing = 10;
    
    for (int i = 0; i < 10; i++) {
        float yPos = startY + i * (toggleHeight + verticalSpacing);
        toggles.emplace_back(startX, yPos, toggleWidth, toggleHeight);
    }
    
    while (!WindowShouldClose()) {
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();
 
        if (currentWidth != screenWidth || currentHeight != screenHeight) {
            float newStartX = 50;
            float newStartY = 50;
            
            if (currentHeight < 700) {
                newStartY = 20;
            }
            
            for (int i = 0; i < toggles.size(); i++) {
                float yPos = newStartY + i * (toggleHeight + verticalSpacing);
                toggles[i].SetPosition(newStartX, yPos);
            }
        }
        
        for (auto& toggle : toggles) {toggle.update();}
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
    
            for (auto& toggle : toggles) {toggle.draw();}
            
        EndDrawing();
    }
    CloseWindow();
    
}