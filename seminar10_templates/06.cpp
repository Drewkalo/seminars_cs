#include <iostream>

template<typename T, T N>
class Modular {
private:
    T value;
    T normalize(T v) const {
        if (N == 0) return v;
        v %= N;
        if (v < 0) {
            v += N;
        }
        return v;
    }
public:
    Modular(T v = 0) : value(normalize(v)) {}
    Modular(const Modular& other) : value(other.value) {}
    
    Modular& operator=(const Modular& other) {
        if (this != &other) {
            value = other.value;
        }
        return *this;
    }

    T getValue() const {
        return value;
    }
    
    Modular operator+(const Modular& other) const {return Modular(value + other.value);}
    Modular operator-(const Modular& other) const {return Modular(value - other.value);}
    Modular operator*(const Modular& other) const {return Modular(value * other.value);}
    Modular operator+(T v) const {return Modular(value + normalize(v));}
    Modular operator-(T v) const {return Modular(value - normalize(v));}
    Modular operator*(T v) const {return Modular(value * normalize(v));}
    Modular& operator+=(const Modular& other) {*this = *this + other;return *this;}
    Modular& operator-=(const Modular& other) {*this = *this - other;return *this;}
    Modular& operator*=(const Modular& other) {*this = *this * other;return *this;}
    Modular operator-() const {return Modular(-value);}

    template<typename U, U M>
    explicit Modular(const Modular<U, M>& other) : value(normalize(static_cast<T>(other.getValue()))) {}

    template<typename U, U M>
    Modular& operator=(const Modular<U, M>& other) {
        value = normalize(static_cast<T>(other.getValue()));
        return *this;
    }

    template<typename TT, TT NN>
    friend std::ostream& operator<<(std::ostream& os, const Modular<TT, NN>& m);
};

template<typename T, T N>
std::ostream& operator<<(std::ostream& os, const Modular<T, N>& m) {
    os << m.value;
    return os;
}

int main() {
    Modular<int, 7> a(10);
    std::cout << "a(10) (mod 7): " << a << std::endl; // Напечатает 3

    // a = (a + 8) * 4; // Напечатает 2
    // a = (3 + 8) * 4 = 11 * 4 = 44
    // 44 mod 7 = 2
    a = (a + 8) * 4; 
    std::cout << "a = (a + 8) * 4: " << a << std::endl; // Напечатает 2
    Modular<int, 7> b(a);
    // b + 2 = 2 + 2 = 4 (mod 7)
    b += 2; 

    // a - b = 2 - 4 = -2 (mod 7) = 5
    a = a - b; 
    std::cout << "a = a - b: " << a << std::endl; // Напечатает 5


    // a = 5 (тип int), c (mod 3)
    // 5 mod 3 = 2
    Modular<short, 3> c(a); // Используется конструктор (7)
    std::cout << "c(a) (mod 3): " << c << std::endl; // Напечатает 2
    
    // Дополнительная проверка: унарный минус
    Modular<int, 7> d(6); // 6 mod 7
    Modular<int, 7> e = -d; // -6 mod 7 = 1
    std::cout << "-d (-6 mod 7): " << e << std::endl; // Напечатает 1
}