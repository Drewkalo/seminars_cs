#include <iostream>
#include "C:\Users\dinos\Desktop\seminars_cs\seminar8_encapsulation\code\circle\point.hpp"
#include <cmath>
using std::cout, std::endl;
//Возможно, стоит сравнивать float'ы с некоторой точностью Epsilon
class Circle
{
private:
    Point center;
    float radius;

public:
    Circle(const Point& center, float radius) {
        this->center = center;
        this->radius = radius;
    }

    Circle() {
        center = Point();
        radius = 1;
    }

    Circle(const Circle& circle) {
        center = circle.center;
        radius = circle.radius;
    }

    float getRadius() const {
        return radius;
    }

    void setRadius(float radius) {
        if (radius < 0) {
            cout << "The radius cannot be negative" << endl;
            return;
        }
        this->radius = radius;
    }

    const Point& getCenter() const {
        return center;
    }

    void setCenter(const Point& center) {
        this->center = center;
    }

    float area() const {
        return (std::numbers::pi * radius * radius);
    }

    float distance(const Point& p) const {
        float temp_dist = center.distance(p);
        if (temp_dist >= radius)
            return temp_dist - radius;
        return radius - temp_dist;
    }

    void move(const Point& p) {
        center.setX(center.getX() + p.getX());
        center.setY(center.getY() + p.getY());
    }

    
    bool isColliding(const Circle& c) const {
        float distance = center.distance(c.center);
        return distance <= (radius + c.radius);
    }
};

int main()
{
    Point p = {7, -1};
    Point q = {-4, 2};
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    cout << "p + q = " << p + q << endl;

    Circle a({4, 1}, 3);
    Circle b;

    cout << "Circle a: center: " << a.getCenter() << " radius: " << a.getRadius() << endl; 
    cout << "Circle b: center: " << b.getCenter() << " radius: " << b.getRadius() << endl;

    cout << "Area of a = " << a.area() << endl;
    cout << "Distance from point p to circle a = " << a.distance(p) << endl;

    cout << "Collisions:" << endl;
    if (a.isColliding(b))
        cout << "Yes, a is colliding b" << endl;
    else
        cout << "No, a isn't colliding b" << endl;

    cout << "Moving b by {1, 1}:" << endl;
    b.move({1, 1});
    if (a.isColliding(b))
        cout << "Yes, a is colliding b" << endl;
    else
        cout << "No, a isn't colliding b" << endl;
}