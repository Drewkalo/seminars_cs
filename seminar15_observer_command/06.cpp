#include "raylib.h"
#include <vector>
#include "button.hpp"

float getRandomFloat(float min, float max) { return GetRandomValue(0, 10000) / 10000.0f * (max - min) + min; }
Color getRandomColor() { return {(unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255}; }

struct Shape {
    virtual void draw() = 0;
    virtual void setPosition(Vector2 p) = 0;
    virtual Vector2 getPosition() = 0;
    virtual void setColor(Color c) = 0;
    virtual Color getColor() = 0;
    virtual Shape* clone() = 0; 
    virtual ~Shape() = default;
};

class CircleShape : public Shape {
private: Vector2 mPosition {}; float mRadius; Color mColor {WHITE};
public:
    CircleShape(float r) : mRadius(r) {}
    void draw() override { DrawCircleV(mPosition, mRadius, mColor); }
    void setPosition(Vector2 p) override { mPosition = p; }
    Vector2 getPosition() override { return mPosition; }
    void setColor(Color c) override { mColor = c; }
    Color getColor() override { return mColor; }
    Shape* clone() override {
        CircleShape* copy = new CircleShape(mRadius);
        copy->setPosition(mPosition); copy->setColor(mColor); return copy;
    }
};

class ShapePool {
private: Rectangle mField; std::vector<Shape*> mShapes;
public:
    ShapePool(Vector2 position, Vector2 size) { mField = {position.x, position.y, size.x, size.y}; }
    ~ShapePool() { clear(); }
    void addShape(Shape* p) { mShapes.push_back(p); }
    size_t getNumberOfShapes() const { return mShapes.size(); }
    Shape& getShape(size_t index) { return *mShapes.at(index); }
    Vector2 getPosition() const { return {mField.x, mField.y}; }
    Vector2 getSize() const { return {mField.width, mField.height}; }
    void clear() { for (auto p : mShapes) delete p; mShapes.clear(); }
    std::vector<Shape*>& getShapesRaw() { return mShapes; }
    void draw() const {
        DrawRectangleRec(mField, {30, 30, 30, 255});
        for (auto p : mShapes) p->draw();
        DrawRectangleLinesEx(mField, 2, BLUE);
    }
};

class Command {
public:
    virtual void execute() = 0;
    virtual void unexecute() = 0;
    virtual Command* clone() = 0;
    virtual ~Command() = default;
};

class AllRandomColorsCommand : public Command {
private:
    ShapePool& mPool; std::vector<Color> mOldColors;
public:
    AllRandomColorsCommand(ShapePool& pool) : mPool(pool) {}
    void execute() override {
        mOldColors.clear();
        for (size_t i = 0; i < mPool.getNumberOfShapes(); ++i) {
            mOldColors.push_back(mPool.getShape(i).getColor());
            mPool.getShape(i).setColor(getRandomColor());
        }
    }
    void unexecute() override {
        for (size_t i = 0; i < mOldColors.size() && i < mPool.getNumberOfShapes(); ++i) {
            mPool.getShape(i).setColor(mOldColors[i]);
        }
    }
    Command* clone() override { return new AllRandomColorsCommand(mPool); }
};

class ControlPanel {
private:
    std::vector<Button*> mButtons;
    std::vector<Command*> mCommands;
    std::vector<Command*> mHistory;

public:
    ~ControlPanel() {
        for (auto p : mButtons) delete p;
        for (auto p : mCommands) delete p;
        for (auto p : mHistory) delete p;
    }
    void addButton(Button* pb, Command* pc) { mButtons.push_back(pb); mCommands.push_back(pc); }
    void draw() { for (auto p : mButtons) p->draw(); }
    
    void update() {
        for (size_t i = 0; i < mButtons.size(); ++i) {
            if (mButtons[i]->handle()) {
                Command* copy = mCommands[i]->clone();
                copy->execute();
                mHistory.push_back(copy);
            }
        }
    }

    void undo() {
        if (!mHistory.empty()) {
            Command* lastCmd = mHistory.back();
            lastCmd->unexecute();
            mHistory.pop_back();
            delete lastCmd;
        }
    }
};

int main() {
    InitWindow(800, 800, "Command Task 6 - Undo System");
    SetTargetFPS(60);

    ShapePool pool({300, 50}, {450, 700});
    pool.addShape(new CircleShape(40)); pool.getShape(0).setPosition({450, 200});
    pool.addShape(new CircleShape(50)); pool.getShape(1).setPosition({550, 400});

    ControlPanel control;
    control.addButton(new Button({40, 80, 240, 40}, "Random Colors"), new AllRandomColorsCommand(pool));
  
    Button undoButton({40, 700, 240, 40}, "Undo Last Action");

    while (!WindowShouldClose()) {
        control.update();
        if (undoButton.handle()) { control.undo(); }

        BeginDrawing();
        ClearBackground(BLACK);
        pool.draw();
        control.draw();
        undoButton.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}