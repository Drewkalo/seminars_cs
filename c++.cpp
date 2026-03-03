#include <iostream>

struct Alice
{
    int x;
    void func() const {std::cout << "Alice " << x << std::endl;}
};

struct Bob : public Alice
{
    int y;
    void func() const {std::cout << "Bob " << x << " " << y << std::endl;}
};

struct Casper : public Bob
{
    int z;
    void func() const {std::cout << "Casper " << x << " " << y << " " << z << std::endl;}
};

int main() {
    Alice a {10};
    Bob b {20, 30};
    Casper c {40, 50, 60};
    Bob* p = &c;
    p->func();
}