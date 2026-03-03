#include "raylib.h"
#include <iostream>
#include <algorithm>

class Slider
{
protected:
    Rectangle mTrackRect{};
    Rectangle mThumbRect{};

    bool mIsPressed{false};

public:
    Slider(Vector2 centerPosition, Vector2 trackSize, Vector2 thumbSize)
    {
        mTrackRect.width = trackSize.x;
        mTrackRect.height = trackSize.y;
        mTrackRect.x = centerPosition.x - trackSize.x / 2.0f;
        mTrackRect.y = centerPosition.y - trackSize.y / 2.0f;

        mThumbRect.width = thumbSize.x;
        mThumbRect.height = thumbSize.y;
        mThumbRect.x = centerPosition.x - thumbSize.x / 2.0f;
        mThumbRect.y = centerPosition.y - thumbSize.y / 2.0f;
    }

    void draw()
    {
        DrawRectangleRec(mTrackRect, {200, 200, 220, 255});
        DrawRectangleRec(mThumbRect, {150, 150, 240, 255});
    }

    void setRestrictedThumbPosition(Vector2 position)
    {
        float min = mTrackRect.x;
        float max = mTrackRect.x + mTrackRect.width;
        float clampedX = std::clamp(position.x, min, max);
        mThumbRect.x = clampedX - mThumbRect.width / 2.0f;
    }

    bool handleEvent()
    {
        Vector2 mousePosition = GetMousePosition();
        bool result = false;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePosition, mThumbRect) ||
                CheckCollisionPointRec(mousePosition, mTrackRect))
            {
                mIsPressed = true;
                setRestrictedThumbPosition(mousePosition);
                result = true;
            }
        }

        if (mIsPressed && (GetMouseDelta().x != 0 || GetMouseDelta().y != 0))
        {
            setRestrictedThumbPosition(mousePosition);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            mIsPressed = false;
        }

        return result;
    }

    bool isPressed() const
    {
        return mIsPressed;
    }

    float getValue() const
    {
        float start = mTrackRect.x;
        float finish = mTrackRect.x + mTrackRect.width;
        float position = mThumbRect.x + mThumbRect.width / 2.0f;
        return 100.0f * (position - start) / (finish - start);
    }
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Color slider");
    SetTargetFPS(60);
    
    Slider redSlider({200, 300}, {200, 10}, {20, 30});
    Slider greenSlider({200, 400}, {200, 10}, {20, 30});
    Slider blueSlider({200, 500}, {200, 10}, {20, 30});
    
    float redValue = 50.0f;
    float greenValue = 50.0f;
    float blueValue = 50.0f;
    
    while (!WindowShouldClose())
    {
        if (redSlider.handleEvent())
        {
            redValue = redSlider.getValue();
        }
        
        if (greenSlider.handleEvent())
        {
            greenValue = greenSlider.getValue();
        }
        
        if (blueSlider.handleEvent())
        {
            blueValue = blueSlider.getValue();
        }
        
        if (redSlider.isPressed())
        {
            redValue = redSlider.getValue();
        }
        
        if (greenSlider.isPressed())
        {
            greenValue = greenSlider.getValue();
        }
        
        if (blueSlider.isPressed())
        {
            blueValue = blueSlider.getValue();
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        Color circleColor = {
            (unsigned char)(redValue * 2.55f),
            (unsigned char)(greenValue * 2.55f),
            (unsigned char)(blueValue * 2.55f),
            255
        };
        
        DrawCircle(screenWidth / 2 + 150, 300, 200, circleColor);
        
        redSlider.draw();
        greenSlider.draw();
        blueSlider.draw();
        
        DrawText("RED", 200, 320, 20, RED);
        DrawText("GREEN", 200, 420, 20, GREEN);
        DrawText("BLUE", 200, 520, 20, BLUE);
        
        DrawText(TextFormat("R: %.0f", redValue), 120, 320, 20, DARKGRAY);
        DrawText(TextFormat("G: %.0f", greenValue), 120, 420, 20, DARKGRAY);
        DrawText(TextFormat("B: %.0f", blueValue), 120, 520, 20, DARKGRAY);
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}