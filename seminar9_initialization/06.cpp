#include <iostream>
class RestrictWrapper {
private:
    int& a;
    const int maxValue;
    const int minValue;
    int get_counter;
    int set_counter;
public:
    RestrictWrapper(int& x, const int& min, const int& max) : a(x), maxValue(max), minValue(min), set_counter(), get_counter() {
        if (x < minValue) {a = minValue;}
        else if (x > maxValue) {a = maxValue;}
        else {a = x;}
    }

    int get() {get_counter++; return a;}

    void set(const int& x) {
        if (x < minValue) {a = minValue;}
        else if (x > maxValue) {a = maxValue;}
        else {a = x;}
        set_counter++; 
    }

    int getCount() const {return get_counter;}
    int setCount() const {return set_counter;}


};
int main()
{
    int x = 100;
    RestrictWrapper w(x, 0, 300);
    std::cout << w.get() << std::endl; // Напечатает 100
    w.set(-200);
    std::cout << w.get() << std::endl; // Напечатает 0
    w.set(300);
    w.set(400);
    w.set(500);
    std::cout << w.get() << std::endl; // Напечатает 300
    std::cout << w.getCount() << std::endl; // Напечатает 3
    std::cout << w.setCount() << std::endl; // Напечатает 4
}