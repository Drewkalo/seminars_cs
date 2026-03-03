#include "raylib.h"
#include <string>
#include "C:\Users\dinos\Desktop\cs_mipt_course\module3_oop\seminar2_inheritance\homework\button.cpp"
#include <iostream>

class BaseWindow {
private:
    static constexpr float dragAreaHeight = 30.0f;

    Rectangle mBaseRect{};
    Rectangle mDragRect{};

    bool mIsDragged{false};

    Vector2 mDragBaseDistance{};
    Vector2 mOffset{};

    Color baseColor {};
    Color dragColor {};

public:
    BaseWindow(Rectangle borders, Color baseColor, Color dragColor) {
        mDragRect = { borders.x, borders.y, borders.width, dragAreaHeight };
        mBaseRect = { borders.x, borders.y + dragAreaHeight, borders.width, borders.height - dragAreaHeight };

        mDragBaseDistance = {
            mDragRect.x - mBaseRect.x,
            mDragRect.y - mBaseRect.y
        };

        this->baseColor = baseColor;
        this->dragColor = dragColor;
    }

    bool onMousePressed(Vector2 mousePosition) {
        if (CheckCollisionPointRec(mousePosition, mDragRect))
        {
            mIsDragged = true;
            mOffset = {
                mousePosition.x - mDragRect.x,
                mousePosition.y - mDragRect.y
            };
        }
        return mIsDragged;
    }

    void onMouseReleased() {mIsDragged = false;}

    void onMouseMoved(Vector2 mousePosition) {
        if (mIsDragged)
        {
            mDragRect.x = mousePosition.x - mOffset.x;
            mDragRect.y = mousePosition.y - mOffset.y;

            mBaseRect.x = mDragRect.x - mDragBaseDistance.x;
            mBaseRect.y = mDragRect.y - mDragBaseDistance.y;
        }
    }

    void handleEvents() {
        Vector2 mousePosition = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {onMousePressed(mousePosition);}

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {onMouseReleased();}

        if (GetMouseDelta().x != 0 || GetMouseDelta().y != 0) {onMouseMoved(mousePosition);}
    }

    void setBaseSize(Vector2 sz) { mBaseRect.width = sz.x; mBaseRect.height = sz.y; }
    void setDragSize(Vector2 sz) { mDragRect.width = sz.x; mDragRect.height = sz.y; }

    void setPosition(Vector2 p) {
        mBaseRect.x = p.x;
        mBaseRect.y = p.y;

        mDragRect.x = mBaseRect.x + mDragBaseDistance.x;
        mDragRect.y = mBaseRect.y + mDragBaseDistance.y;
    }

    void draw() const {
        DrawRectangleRec(mBaseRect, baseColor);
        DrawRectangleRec(mDragRect, dragColor);
    }

    Vector2 getBasePosition() const {return {mBaseRect.x, mBaseRect.y};}
    
    float getBaseWidth() const {return mBaseRect.width;}
    float getBaseHeight() const {return mBaseRect.height;}

    void setbaseColor(Color color) {baseColor = color;}
    void setdragColor(Color color) {dragColor = color;}
};

class MessageWindow : public BaseWindow {
private:
    std::string text{};
    Color textColor {BLACK};
    int fontSize {20};
public:
    MessageWindow(Rectangle borders, std::string text, Color baseColor, Color dragColor) : BaseWindow(borders, baseColor, dragColor), text(text) {}

    void draw() const {
        BaseWindow::draw();
    
        Vector2 basePos = getBasePosition();
        float baseWidth = getBaseWidth();
        
        int textWidth = MeasureText(text.c_str(), fontSize);
        float textX = basePos.x + (baseWidth - textWidth) / 2;
        float textY = basePos.y + 20;
        
        DrawText(text.c_str(), textX, textY, fontSize, textColor);
    }
    
    void setText(const std::string& newText) {text = newText;}
    
    void setTextColor(Color color) {textColor = color;}
    
    void setFontSize(int size) {fontSize = size;}
};

class ErrorWindow : public MessageWindow {
public:
    ErrorWindow(Rectangle borders, std::string text, Color baseColor, Color dragColor) 
        : MessageWindow(borders, text, RED, WHITE) {}
};

class DoneWindow : public MessageWindow {
public:
    DoneWindow(Rectangle borders, std::string text, Color baseColor, Color dragColor) 
        : MessageWindow(borders, text, GREEN, WHITE) {}
};

class QuestionWindow : public BaseWindow {
private:
    std::string questionText;
    Color textColor{BLACK};
    int fontSize{20};
    Button okButton;
    Button cancelButton;

public:
    QuestionWindow(Rectangle borders, std::string text, Color baseColor, Color dragColor) 
        : BaseWindow(borders, baseColor, dragColor), questionText(text), okButton({{borders.x + 50, borders.y + borders.height - 60, 80, 30}, 20, "OK"})
        , cancelButton({{borders.x + borders.width - 130, borders.y + borders.height - 60, 80, 30}, 20, "Cancel"})
    {}
    
    void handleEvents() {
        BaseWindow::handleEvents();
        
        Vector2 basePos = getBasePosition();
        float baseWidth = getBaseWidth();
        
        Rectangle currentBaseRect = {basePos.x, basePos.y, baseWidth, 0};
        
        okButton = Button(
            {basePos.x + 50, 
             basePos.y + (getBaseHeight() - 60), 
             80, 30}, 
            20, "OK"
        );
        
        cancelButton = Button(
            {basePos.x + baseWidth - 130, 
             basePos.y + (getBaseHeight() - 60), 
             80, 30}, 
            20, "Cancel"
        );
        
        if (okButton.handleEvent()) {
            std::cout << "OK" << std::endl;
        }
        
        if (cancelButton.handleEvent()) {
            std::cout << "Cancel" << std::endl;
        }
    }
    
    void draw() const {
        BaseWindow::draw();
        
        Vector2 basePos = getBasePosition();
        float baseWidth = getBaseWidth();
        
        int textWidth = MeasureText(questionText.c_str(), fontSize);
        float textX = basePos.x + (baseWidth - textWidth) / 2;
        float textY = basePos.y + 40;
        
        DrawText(questionText.c_str(), textX, textY, fontSize, textColor);
        
        okButton.draw();
        cancelButton.draw();
    }
    
};
//тесты, созданные нейросетью
//не могу понять, почему при нажатии по кнопкам ничего не выводится на консоль
int main() {
    InitWindow(800, 600, "Windows Test - One Window of Each Type");
    SetTargetFPS(60);

    // Создаем по одному окну каждого типа
    BaseWindow baseWindow({50, 50, 250, 150}, BLUE, LIGHTGRAY);
    
    MessageWindow messageWindow({100, 220, 250, 150}, "Hello, World!", SKYBLUE, DARKBLUE);
    
    ErrorWindow errorWindow({150, 390, 250, 150}, "ERROR: File not found!", RED, MAROON);
    
    DoneWindow doneWindow({400, 50, 250, 150}, "Operation completed!", GREEN, DARKGREEN);
    
    QuestionWindow questionWindow({400, 220, 250, 150}, "Close the Window?", PURPLE, DARKPURPLE);

    while (!WindowShouldClose())
    {
        baseWindow.handleEvents();
        messageWindow.handleEvents();
        errorWindow.handleEvents();
        doneWindow.handleEvents();
        questionWindow.handleEvents();

        BeginDrawing();
        ClearBackground(BLACK);

        baseWindow.draw();
        messageWindow.draw();
        errorWindow.draw();
        doneWindow.draw();
        questionWindow.draw();

        EndDrawing();
    }

    CloseWindow();
}