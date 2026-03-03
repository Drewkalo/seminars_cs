#include <iostream>
#include <cmath>
#include <raylib.h>


class Draggable {
protected:
    Rectangle mRect {};
    Color mColor {};
    bool mIsDragged {false};
    Vector2 mOffset {0.0f, 0.0f};

public:
    Draggable(Vector2 position, Vector2 size, Color color) : mColor{color}
    {
        mRect.x = position.x;
        mRect.y = position.y;
        mRect.width = size.x;
        mRect.height = size.y;
    }

    bool onMousePressed(Vector2 mousePosition)
    {
        if (CheckCollisionPointRec(mousePosition, mRect))
        {
            mIsDragged = true;
            mOffset.x = mousePosition.x - mRect.x;
            mOffset.y = mousePosition.y - mRect.y;
        }
        return mIsDragged;
    }

    void onMouseReleased()
    {
        mIsDragged = false;
    }

    void onMouseMoved(Vector2 mousePosition)
    {
        if (mIsDragged)
        {
            mRect.x = mousePosition.x - mOffset.x;
            mRect.y = mousePosition.y - mOffset.y;
        }
    }

    void handleEvents()
    {
        Vector2 mousePosition = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            onMousePressed(mousePosition);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            onMouseReleased();
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || GetMouseDelta().x != 0 || GetMouseDelta().y != 0)
        {
            onMouseMoved(mousePosition);
        }
    }

    void setColor(Color c)
    {
        mColor = c;
    }

    void setSize(Vector2 sz)
    {
        mRect.width = sz.x;
        mRect.height = sz.y;
    }

    void setPosition(Vector2 pos)
    {
        mRect.x = pos.x;
        mRect.y = pos.y;
    }

    void draw() const
    {
        DrawRectangleRec(mRect, mColor);
    }
};



class DraggableWithColorChange : public Draggable {
private:
    Color dragColor;
    Color baseColor;

public:
    DraggableWithColorChange(Vector2 position, Vector2 size, Color baseColor, Color dragColor) : 
    Draggable(position, size, baseColor), dragColor(dragColor), baseColor(baseColor) {}

    bool onMousePressed(Vector2 mousePosition)
    {
        if (CheckCollisionPointRec(mousePosition, mRect))
        {
            mIsDragged = true;
            mColor = dragColor;
            mOffset.x = mousePosition.x - mRect.x;
            mOffset.y = mousePosition.y - mRect.y;
        }
        return mIsDragged;
    }

    void onMouseReleased()
    {
        mColor = baseColor;
        mIsDragged = false;
    }
    
    void handleEvents()
    {
        Vector2 mousePosition = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            onMousePressed(mousePosition);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            onMouseReleased();
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || GetMouseDelta().x != 0 || GetMouseDelta().y != 0)
        {
            onMouseMoved(mousePosition);
        }
    }
};



// Тест для проверки задания, тест создан нейросетью
void runTest() {
    std::cout << "=== Тестирование DraggableWithColorChange ===\n";
    
    // Создаем объект с изменением цвета
    DraggableWithColorChange testRect{{100, 100}, {200, 400}, BLUE, RED};
    
    // Тест 1: Проверка начального состояния
    std::cout << "Тест 1: Начальный цвет должен быть BLUE\n";
    // Визуально нужно проверить, что прямоугольник синий
    
    // Тест 2: Имитация нажатия на прямоугольник
    std::cout << "Тест 2: При нажатии цвет должен стать RED\n";
    Vector2 mousePos = {150, 200}; // Координаты внутри прямоугольника
    testRect.onMousePressed(mousePos);
    // Визуально проверить, что стал красным
    
    // Тест 3: Проверка перетаскивания
    std::cout << "Тест 3: При перетаскивании цвет остается RED\n";
    testRect.onMouseMoved({200, 250});
    // Должен остаться красным
    
    // Тест 4: Проверка отпускания
    std::cout << "Тест 4: При отпускании цвет возвращается к BLUE\n";
    testRect.onMouseReleased();
    // Должен стать синим
    
    std::cout << "=== Тест завершен. Проверьте визуально ===\n\n";
}

int main()
{
    InitWindow(800, 600, "Draggable Test");
    SetTargetFPS(100);

    // Запускаем автоматический тест в консоли
    runTest();
    
    // Создаем объект с изменением цвета
    DraggableWithColorChange d {{100, 100}, {200, 400}, BLUE, RED};

    while (!WindowShouldClose())
    {
        d.handleEvents();

        BeginDrawing();
        ClearBackground(BLACK);
        d.draw();
        
        EndDrawing();
    }

    CloseWindow();
}