#include "raylib.h"
#include <vector>
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
private: Vector2 mPosition {}; float mRadius; Color mColor {WHITE};
public:
    CircleShape(float r) : mRadius(r) {}
    void draw() override { DrawCircleV(mPosition, mRadius, mColor); }
    void setPosition(Vector2 p) override { mPosition = p; }
    void setColor(Color c) override { mColor = c; }
};

class ShapePool {
private: Rectangle mField; std::vector<Shape*> mShapes;
public:
    ShapePool(Vector2 position, Vector2 size) { mField = {position.x, position.y, size.x, size.y}; }
    ~ShapePool() { for (auto p : mShapes) delete p; }
    void addShape(Shape* p) { mShapes.push_back(p); }
    size_t getNumberOfShapes() const { return mShapes.size(); }
    Shape& getShape(size_t index) { return *mShapes.at(index); }
    Vector2 getPosition() const { return {mField.x, mField.y}; }
    Vector2 getSize() const { return {mField.width, mField.height}; }
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
private: ShapePool& mPool;
public:
    AllRandomColorsCommand(ShapePool& pool) : mPool(pool) {}
    void execute() override { for (size_t i = 0; i < mPool.getNumberOfShapes(); ++i) mPool.getShape(i).setColor(getRandomColor()); }
};

class RandomAllPositionsCommand : public Command {
private: ShapePool& mPool;
public:
    RandomAllPositionsCommand(ShapePool& pool) : mPool(pool) {}
    void execute() override {
        for (size_t i = 0; i < mPool.getNumberOfShapes(); ++i) {
            Vector2 pos = { mPool.getPosition().x + getRandomFloat(50, mPool.getSize().x - 50), mPool.getPosition().y + getRandomFloat(50, mPool.getSize().y - 50) };
            mPool.getShape(i).setPosition(pos);
        }
    }
};

class MultiCommand : public Command {
private:
    std::vector<Command*> mCommands;
public:
    MultiCommand(std::vector<Command*> commands) : mCommands(commands) {}
    ~MultiCommand() { for (auto c : mCommands) delete c; }

    void execute() override {
        for (auto cmd : mCommands) {
            cmd->execute();
        }
    }
};

class ControlPanel {
private: std::vector<Button*> mButtons; std::vector<Command*> mCommands;
public:
    ~ControlPanel() { for (auto p : mButtons) delete p; for (auto p : mCommands) delete p; }
    void addButton(Button* pb, Command* pc) { mButtons.push_back(pb); mCommands.push_back(pc); }
    void draw() { for (auto p : mButtons) p->draw(); }
    void update() { for (size_t i = 0; i < mButtons.size(); ++i) { if (mButtons[i]->handle()) mCommands[i]->execute(); } }
};

int main() {
    InitWindow(800, 800, "Command Task 5 - MultiCommand");
    SetTargetFPS(60);

    ShapePool pool({300, 50}, {450, 700});
    pool.addShape(new CircleShape(40)); pool.getShape(0).setPosition({400, 200});
    pool.addShape(new CircleShape(40)); pool.getShape(1).setPosition({500, 400});

    ControlPanel control;
    
    std::vector<Command*> macro;
    macro.push_back(new AllRandomColorsCommand(pool));
    macro.push_back(new RandomAllPositionsCommand(pool));

    control.addButton(new Button({40, 80, 240, 40}, "Color & Position Multi"), new MultiCommand(macro));

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