#include <iostream>
#include <cmath>
#include <numbers>

struct Vector2f {
    float x, y;
};

Vector2f operator+(Vector2f left, Vector2f right) {
    Vector2f result = {left.x + right.x, left.y + right.y};
    return result;
}

Vector2f operator*(Vector2f left, float right) {
    Vector2f result = {left.x * right, left.y * right};
    return result;
}

Vector2f operator*(float left, Vector2f right) {
    Vector2f result = {left * right.x, left * right.y};
    return result;
}

Vector2f& operator+=(Vector2f& left, Vector2f right) {
    left.x += right.x;
    left.y += right.y;
    return left;
}

float getDistance(Vector2f a, Vector2f b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

std::ostream& operator<<(std::ostream& out, Vector2f right) {
    out << "(" << right.x << ", " << right.y << ")";
    return out;
}



class Shape {
private:
    Vector2f mPosition;

public:
    Shape(Vector2f position) : mPosition(position) {}

    Vector2f getPosition() {return mPosition;}

    void setPosition(Vector2f newPosition) {mPosition = newPosition;}

    void move(Vector2f change) {mPosition += change;}
};



class Circle : public Shape {
private:
    float mRadius;

public:
    Circle(float radius) : Shape({0, 0}),  mRadius(radius) {}

    float calculatePerimeter() {return 2 * std::numbers::pi * mRadius;}
};



class Rectangle : public Shape {
private:
    float mWidth;
    float mHeight;

public:
    Rectangle(float width, float height) : Shape({0, 0}), mWidth(width), mHeight(height) {}

    float calculatePerimeter(){return 2 * (mWidth + mHeight);}
};



class Triangle : public Shape{
private:
    Vector2f mPointA;
    Vector2f mPointB;
    Vector2f mPointC;

public:
    Triangle(Vector2f pointA, Vector2f pointB, Vector2f pointC) : Shape({0, 0}), mPointA(pointA), mPointB(pointB), mPointC(pointC) {}

    float calculatePerimeter() {return getDistance(mPointA, mPointB) + getDistance(mPointB, mPointC) + getDistance(mPointC, mPointA);}
};


int main() //тесты сгенерированы нейросетью
{
    Circle a(10);
    std::cout << "Circle perimeter: " << a.calculatePerimeter() << std::endl;
    std::cout << "Circle position: " << a.getPosition() << std::endl;
    
    a.move({5, 3});
    std::cout << "After move: " << a.getPosition() << std::endl;  // Должно быть (5, 3)

    Rectangle b(100, 200);
    std::cout << "\nRectangle perimeter: " << b.calculatePerimeter() << std::endl;
    std::cout << "Rectangle position: " << b.getPosition() << std::endl;
    
    b.move({-10, 20});
    std::cout << "After move: " << b.getPosition() << std::endl;  // Должно быть (-10, 20)

    Triangle c({5, 2}, {-7, 5}, {4, 4});
    std::cout << "\nTriangle perimeter: " << c.calculatePerimeter() << std::endl;
    std::cout << "Triangle position: " << c.getPosition() << std::endl;
    
    c.move({2, -2});
    std::cout << "After move: " << c.getPosition() << std::endl;  // Должно быть (2, -2)
}