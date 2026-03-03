#include "raylib.h"
#include <vector>
#include <string>

class DropList {
private:
    Rectangle bounds;
    std::vector<std::string> items;
    int selectedIndex;
    bool expanded;
    Color backgroundColor;
    Color textColor;
    Color borderColor;
    Color hoverColor;
    int fontSize;
    int itemHeight;

public:
    DropList(float x, float y, float width, const std::vector<std::string>& listItems)
        : bounds{ x, y, width, 30 }, items(listItems), selectedIndex(0), expanded(false), backgroundColor(RAYWHITE)
        , textColor(BLACK), borderColor(GRAY), hoverColor(LIGHTGRAY), fontSize(20), itemHeight(30)
    {if (!items.empty()) selectedIndex = 0;}

    void update() {
        Vector2 mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, bounds)) {if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) expanded = !expanded;}
        
        if (expanded) {
            for (size_t i = 0; i < items.size(); i++) {
                Rectangle itemBounds = {
                    bounds.x,
                    bounds.y + bounds.height + i * itemHeight,
                    bounds.width,
                    (float)itemHeight
                };
                
                if (CheckCollisionPointRec(mousePoint, itemBounds)) {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        selectedIndex = i;
                        expanded = false;
                    }
                }
            }
        }
    }

    void draw() {
        DrawRectangleRec(bounds, backgroundColor);
        DrawRectangleLinesEx(bounds, 2, borderColor);
        
        if (selectedIndex >= 0 && selectedIndex < items.size()) {
            DrawText(items[selectedIndex].c_str(), 
                    bounds.x + 5, bounds.y + 5, 
                    fontSize, textColor);
        }
        
        DrawTriangle(
            Vector2{ bounds.x + bounds.width - 20, bounds.y + 10 },
            Vector2{ bounds.x + bounds.width - 10, bounds.y + 20 },
            Vector2{ bounds.x + bounds.width - 30, bounds.y + 20 },
            borderColor
        );
        
        if (expanded) {
            for (size_t i = 0; i < items.size(); i++) {
                Rectangle itemBounds = {
                    bounds.x,
                    bounds.y + bounds.height + i * itemHeight,
                    bounds.width,
                    (float)itemHeight
                };
                
                Color itemColor = backgroundColor;
                Vector2 mousePoint = GetMousePosition();
                if (CheckCollisionPointRec(mousePoint, itemBounds)) {
                    itemColor = hoverColor;
                }
                
                DrawRectangleRec(itemBounds, itemColor);
                DrawRectangleLinesEx(itemBounds, 1, borderColor);
                
                DrawText(items[i].c_str(), 
                        itemBounds.x + 5, itemBounds.y + 5, 
                        fontSize, textColor);
            }
        }
    }

    std::string GetSelectedItem() const {
        if (selectedIndex >= 0 && selectedIndex < items.size()) {return items[selectedIndex];}
        return "";
    }
};

void drawShape(const std::string& shape) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Vector2 center = { (float)screenWidth / 2, (float)screenHeight / 2 };
    float size = 100.0f;
    
    if (shape == "Circle") {
        DrawCircleV(center, size, BLUE);
    }
    else if (shape == "Square") {
        DrawRectangleV(
            Vector2{ center.x - size / 2, center.y - size / 2 },
            Vector2{ size, size },
            GREEN
        );
    }
    else if (shape == "Triangle") {
        DrawTriangle(
            Vector2{ center.x, center.y - size },
            Vector2{ center.x - size * 0.866f, center.y + size * 0.5f },
            Vector2{ center.x + size * 0.866f, center.y + size * 0.5f },
            RED
        );
    }
}

int main() {
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    
    InitWindow(screenWidth, screenHeight, "DropList with shapes!");
    SetTargetFPS(60);

    std::vector<std::string> shapes = { "Circle", "Square", "Triangle" };
    DropList dropList(50, 50, 200, shapes);
    
    while (!WindowShouldClose()) {
        
        dropList.update();
        
        BeginDrawing();
        ClearBackground(GetColor(0x181818));
        
        dropList.draw();
        
        std::string selectedShape = dropList.GetSelectedItem();
        if (!selectedShape.empty()) {drawShape(selectedShape);}
        
        EndDrawing();
    }
    
    CloseWindow();
}