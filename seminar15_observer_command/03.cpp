#include "raylib.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "button.hpp"

float getRandomFloat(float min, float max) { return GetRandomValue(0, 10000) / 10000.0f * (max - min) + min; }
int getRandomInt(int min, int max) { return GetRandomValue(min, max); }
Color getRandomColor() { return {(unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255}; }

struct Shape {
    virtual void draw() = 0;
    virtual void rotate(float a) = 0;
    virtual void setPosition(Vector2 p) = 0;
    virtual Vector2 getSize() = 0;
    virtual void setColor(Color c) = 0;
    virtual ~Shape() = default;
};

class RectangleShape : public Shape {
private:
    Vector2 mPosition {}, mSize; float mRotation {0}; Color mColor {};
public:
    RectangleShape(Vector2 size) : mSize(size) {}
    void draw() override { DrawRectanglePro({mPosition.x, mPosition.y, mSize.x, mSize.y}, {mSize.x / 2, mSize.y / 2}, mRotation, mColor); }
    void rotate(float a) override { mRotation += a; }
    void setPosition(Vector2 p) override { mPosition = p; }
    Vector2 getSize() override { return mSize; }
    void setColor(Color c) override { mColor = c; }
};

class CircleShape : public Shape {
private:
    Vector2 mPosition {}; float mRadius, mRotation {0}; Color mColor {}; int mSegments;
public:
    CircleShape(float r, int seg = 32) : mRadius(r), mSegments(seg) {}
    void draw() override { if (mSegments == 3) DrawPoly(mPosition, 3, mRadius, mRotation, mColor); else DrawCircleV(mPosition, mRadius, mColor); }
    void rotate(float a) override { mRotation += a; }
    void setPosition(Vector2 p) override { mPosition = p; }
    Vector2 getSize() override { return {mRadius * 2, mRadius * 2}; }
    void setColor(Color c) override { mColor = c; }
};

class ShapePool {
private:
    Rectangle mField; std::vector<Shape*> mShapes;
public:
    ShapePool(Vector2 position, Vector2 size) { mField = {position.x, position.y, size.x, size.y}; }
    ~ShapePool() { clear(); }
    void addShape(Shape* p) { mShapes.push_back(p); }
    size_t getNumberOfShapes() const { return mShapes.size(); }
    Shape& getShape(size_t index) { return *mShapes.at(index); }
    Vector2 getPosition() const { return {mField.x, mField.y}; }
    Vector2 getSize() const { return {mField.width, mField.height}; }
    void clear() { for (auto p : mShapes) delete p; mShapes.clear(); }
    void draw() const {
        DrawRectangleRec(mField, {30, 30, 30, 255});
        for (auto p : mShapes) p->draw();
        DrawRectangleLinesEx(mField, 2, BLUE);
    }
};

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class AllRandomColorsCommand : public Command {
private:
    ShapePool& mPool;
public:
    AllRandomColorsCommand(ShapePool& pool) : mPool(pool) {}
    void execute() override {
        for (size_t i = 0; i < mPool.getNumberOfShapes(); ++i) {
            mPool.getShape(i).setColor(getRandomColor());
        }
    }
};

class ControlPanel {
private:
    std::vector<Button*> mButtons; std::vector<Command*> mCommands;
public:
    ~ControlPanel() { for (auto p : mButtons) delete p; for (auto p : mCommands) delete p; }
    void addButton(Button* pb, Command* pc) { mButtons.push_back(pb); mCommands.push_back(pc); }
    void draw() { for (auto p : mButtons) p->draw(); }
    void update() {
        for (size_t i = 0; i < mButtons.size(); ++i) {
            if (mButtons[i]->handle()) mCommands[i]->execute();
        }
    }
};

int main() {
    InitWindow(800, 800, "Command Task 3 - All Random Colors");
    SetTargetFPS(60);

    ShapePool pool({300, 50}, {450, 700});
    pool.addShape(new RectangleShape({100, 100}));
    pool.addShape(new CircleShape(50));
    pool.getShape(0).setPosition({400, 200});
    pool.getShape(1).setPosition({600, 400});

    ControlPanel control;
    control.addButton(new Button({40, 80, 240, 40}, "All Random Colors"), new AllRandomColorsCommand(pool));

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