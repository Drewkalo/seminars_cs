#include "raylib.h"
#include <vector>
#include "button.hpp"

struct Shape {
    virtual void draw() = 0;
    virtual void setPosition(Vector2 p) = 0;
    virtual ~Shape() = default;
};

class CircleShape : public Shape {
private: Vector2 mPosition {}; float mRadius; Color mColor {ORANGE};
public:
    CircleShape(float r) : mRadius(r) {}
    void draw() override { DrawCircleV(mPosition, mRadius, mColor); }
    void setPosition(Vector2 p) override { mPosition = p; }
};

class ShapePool {
private:
    Rectangle mField; std::vector<Shape*> mShapes;
public:
    ShapePool(Vector2 position, Vector2 size) { mField = {position.x, position.y, size.x, size.y}; }
    ~ShapePool() { clear(); }
    void addShape(Shape* p) { mShapes.push_back(p); }
    size_t getNumberOfShapes() const { return mShapes.size(); }
    void clear() { for (auto p : mShapes) delete p; mShapes.clear(); }
    Shape& getShape(size_t index) { return *mShapes.at(index); }
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

class ClearAllShapesCommand : public Command {
private:
    ShapePool& mPool;
public:
    ClearAllShapesCommand(ShapePool& pool) : mPool(pool) {}
    void execute() override {
        mPool.clear();
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
    InitWindow(800, 800, "Command Task 4 - Clear Pool");
    SetTargetFPS(60);

    ShapePool pool({300, 50}, {450, 700});
    pool.addShape(new CircleShape(40)); pool.getShape(0).setPosition({400, 200});
    pool.addShape(new CircleShape(50)); pool.getShape(1).setPosition({500, 400});

    ControlPanel control;
    control.addButton(new Button({40, 80, 240, 40}, "Clear Field"), new ClearAllShapesCommand(pool));

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