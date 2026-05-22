#include "raylib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

class Slider;

class Observer
{
public:
    virtual void update(Slider* subject, float value) = 0;
    virtual ~Observer() = default;
};

class Drawable
{
public:
    virtual void draw() const = 0;
    virtual ~Drawable() = default;
};

class Slider : public Drawable
{
private:
    Rectangle mTrack;
    Rectangle mThumb;
    Color mTrackColor {200, 200, 220, 255};
    Color mThumbColor {150, 150, 240, 255};
    bool mIsPressed {false};
    std::set<Observer*> mObservers;

public:
    Slider(Vector2 center, Vector2 trackSize, Vector2 thumbSize)
    {
        mTrack = {center.x - trackSize.x / 2, center.y - trackSize.y / 2, trackSize.x, trackSize.y};
        mThumb = {center.x - thumbSize.x / 2, center.y - thumbSize.y / 2, thumbSize.x, thumbSize.y};
    }

    void draw() const override
    {
        DrawRectangleRec(mTrack, mTrackColor);
        DrawRectangleRec(mThumb, mThumbColor);
    }

    void updateInput()
    {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, mThumb) || CheckCollisionPointRec(mouse, mTrack))
            {
                mIsPressed = true;
                mThumb.x = mouse.x - mThumb.width / 2;
                notifyObservers();
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) { mIsPressed = false; }

        if (mIsPressed)
        {
            float min = mTrack.x;
            float max = mTrack.x + mTrack.width;
            float clampedX = std::clamp(mouse.x, min, max);
            mThumb.x = clampedX - mThumb.width / 2;
            notifyObservers();
        }
    }

    float getValue() const
    {
        float part = (mThumb.x + mThumb.width / 2) - mTrack.x;
        return (part / mTrack.width) * 100.0f;
    }

    void addObserver(Observer* p) { mObservers.insert(p); }

    void notifyObservers()
    {
        for (auto p : mObservers)
        {
            p->update(this, getValue());
        }
    }
};

class ComboShape : public Observer, public Drawable
{
private:
    Vector2 mPosition;
    float mSize;
    float mRotation {0.0f};
    Color mColor {255, 0, 0, 255};
    
    Slider* mRotationSlider;
    Slider* mColorSlider;

public:
    ComboShape(Vector2 pos, float size, Slider* rotSlider, Slider* colSlider) 
        : mPosition(pos), mSize(size), mRotationSlider(rotSlider), mColorSlider(colSlider) {}

    void draw() const override
    {
        DrawRectanglePro({mPosition.x, mPosition.y, mSize, mSize}, {mSize / 2, mSize / 2}, mRotation, mColor);
    }

    void update(Slider* subject, float value) override
    {
        if (subject == mRotationSlider)
        {
            mRotation = value * 3.6f;
        }
        else if (subject == mColorSlider)
        {
            mColor = {(unsigned char)(value * 2.55f), 100, (unsigned char)(255 - value * 2.55f), 255};
        }
    }
};

int main()
{
    InitWindow(800, 800, "Observer Task 2 - Two Subjects");
    SetTargetFPS(60);

    Slider sliderRotation({400, 550}, {500, 20}, {25, 40});
    Slider sliderColor({400, 650}, {500, 20}, {25, 40});

    std::vector<Observer*> observers {
        new ComboShape({250, 250}, 80, &sliderRotation, &sliderColor),
        new ComboShape({550, 250}, 120, &sliderRotation, &sliderColor)
    };

    for (auto p : observers) {
        sliderRotation.addObserver(p);
        sliderColor.addObserver(p);
    }

    while (!WindowShouldClose())
    {
        sliderRotation.updateInput();
        sliderColor.updateInput();

        BeginDrawing();
        ClearBackground(BLACK);

        sliderRotation.draw();
        sliderColor.draw();
        
        DrawText("Rotation Slider", 150, 520, 20, LIGHTGRAY);
        DrawText("Color Slider", 150, 620, 20, LIGHTGRAY);

        for (auto p : observers) { dynamic_cast<Drawable*>(p)->draw(); }

        EndDrawing();
    }

    for (auto p : observers) { delete p; }
    CloseWindow();
    return 0;
}