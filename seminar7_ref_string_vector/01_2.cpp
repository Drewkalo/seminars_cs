#include <iostream>
namespace mipt {
namespace fefm {
struct Point {
    int x, y;
};
}
namespace frtk {
void print(fefm::Point p) {
    std::cout << p.x << " " << p.y << std::endl;
}
}
}
using namespace mipt;
using namespace fefm;
using namespace frtk;
int main() {
    Point a = {10, 20};
    print(a);
}