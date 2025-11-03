#include <iostream>
void cube(int& a) {
    a = a * a * a;
}
int main() {
    int a = 5;
    cube(a);
    std::cout << a << std::endl; // Должно напечатать 125
}
