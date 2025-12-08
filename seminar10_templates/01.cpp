#include <iostream>
template <typename T>
T cube(T x) {
    return x * x * x;
}
int main() {
    int a = 4;
    double b = 4.5;
    float c = 9.99;
    std::cout << cube(a) << " " << cube(b) << " " << cube(c) << std::endl;
}