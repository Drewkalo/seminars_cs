#include "raylib.h"
#include <vector>
#include <memory>
#include "button.hpp"

float getRandomFloat(float min, float max) { return GetRandomValue(0, 10000) / 10000.0f * (max - min) + min; }
Color getRandomColor() { return {(unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255}; }

struct Shape {
    virtual void draw() = 0;
    virtual void setPosition(Vector2 p) = 0;
    virtual void setColor(Color c) = 0;
    virtual ~Shape() = default;
};

class CircleShape : public Shape {
private: Vector2 mPosition {}; float mRadius; Color mColor {GREEN};
public:
    CircleShape(float r) : mRadius(r) {}
    void draw() override { DrawCircleV(mPosition, mRadius, mColor); }
    void setPosition(Vector2 p) override { mPosition = p; }
    void setColor(Color c) override { mColor = c; }
};

class ShapePool {
private:
    Rectangle mField; 
    std::vector<std::unique_ptr<Shape>> mShapes;
public:
    ShapePool(Vector2 position, Vector2 size) { mField = {position.x, position.y, size.x, size.y}; }
    void addShape(std::unique_ptr<Shape> p) { mShapes.push_back(std::move(p)); }
    size_t getNumberOfShapes() const { return mShapes.size(); }
    Shape& getShape(size_t index) { return *mShapes.at(index); }
    void draw() const {
        DrawRectangleRec(mField, {30, 30, 30, 255});
        for (const auto& p : mShapes) p->draw();
        DrawRectangleLinesEx(mField, 2, BLUE);
    }
};

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class AllRandomColorsCommand : public Command {
private: ShapePool& mPool;
public:
    AllRandomColorsCommand(ShapePool& pool) : mPool(pool) {}
    void execute() override { for (size_t i = 0; i < mPool.getNumberOfShapes(); ++i) mPool.getShape(i).setColor(getRandomColor()); }
};

class ControlPanel {
private:
    std::vector<std::unique_ptr<Button>> mButtons;
    std::vector<std::unique_ptr<Command>> mCommands;
public:
    // Деструктор пуст - утечки исключены
    void addButton(std::unique_ptr<Button> pb, std::unique_ptr<Command> pc) { 
        mButtons.push_back(std::move(pb)); 
        mCommands.push_back(std::move(pc)); 
    }
    void draw() { for (const auto& p : mButtons) p->draw(); }
    void update() { for (size_t i = 0; i < mButtons.size(); ++i) { if (mButtons[i]->handle()) mCommands[i]->execute(); } }
};

int main() {
    InitWindow(800, 800, "Command Task 7 - Unique Pointers");
    SetTargetFPS(60);

    ShapePool pool({300, 50}, {450, 700});
    auto circle1 = std::make_unique<CircleShape>(40); circle1->setPosition({400, 200});
    auto circle2 = std::make_unique<CircleShape>(50); circle2->setPosition({500, 400});
    pool.addShape(std::move(circle1));
    pool.addShape(std::move(circle2));

    ControlPanel control;
    control.addButton(
        std::make_unique<Button>(Rectangle{40, 80, 240, 40}, "UniquePtr Random Colors"), 
        std::make_unique<AllRandomColorsCommand>(pool)
    );

    while (!WindowShouldClose()) {
        control.update();
        BeginDrawing();
        ClearBackground(BLACK);
        pool.draw();
        control.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}