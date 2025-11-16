#include <iostream>
using std::cout, std::endl;
struct Vector2f {
    float x;
    float y;
};

Vector2f operator+(const Vector2f& a, const Vector2f& b) {
    return {a.x + b.x, a.y + b.y};
}

Vector2f operator-(const Vector2f& a, const Vector2f& b) {
    return {a.x - b.x, a.y - b.y};
}

Vector2f operator*(const Vector2f& a, float b) {
    return {a.x * b, a.y * b};
}

Vector2f operator*(float b, const Vector2f& a) {
    return a * b;
}

Vector2f operator/(const Vector2f& a, float b) {
    return {a.x / b, a.y / b};
}

Vector2f operator/(float b, const Vector2f& a) {
    return a / b;
}

float operator*(const Vector2f& a, const Vector2f& b) {
    return a.x * b.x + a.y * b.y;
}

Vector2f operator+(const Vector2f& a) {
    return a;
}

Vector2f operator-(const Vector2f& a) {
    return {-a.x, -a.y};
}

bool operator==(const Vector2f& a, const Vector2f& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const Vector2f& a, const Vector2f& b) {
    return !(a == b);
}

Vector2f& operator+=(Vector2f& a, const Vector2f& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

Vector2f& operator-=(Vector2f& a, const Vector2f& b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

Vector2f& operator*=(Vector2f& a, float b) {
    a.x *= b;
    a.y *= b;
    return a;
}

Vector2f& operator/=(Vector2f& a, float b) {
    a.x /= b;
    a.y /= b;
    return a;
}

std::ostream& operator<<(std::ostream& out, const Vector2f& a) {
    out << '(' << a.x << ',' << a.y << ')';
    return out;
}

std::istream& operator>>(std::istream& in, Vector2f& a) {
    in >> a.x >> a.y;
    return in;
}

int main() {
    Vector2f a = {1.0, 2.0};
    Vector2f b = {4.0, -1.0};
    cout << "a = " << a << endl << "b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "-a = " << -a << endl;
    cout << "Scalar product of a and b = " << a * b << endl;
    a /= 5;
    cout << "a after a /= 5;" << a << endl;
    a += b;
    cout << "a after a+= b;" << a << endl;
}
