#include <iostream>
int& getRefToMax(int& pa, int& pb) {
    if (pa > pb)
        return pa;
    else
        return pb;
}
int main() {
    int a = 10;
    int b = 20;
    getRefToMax(a, b) += 1;
    std::cout << a << " " << b << std::endl;
}