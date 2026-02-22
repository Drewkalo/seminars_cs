#include <iostream>
#include <vector>
#include <dlfcn.h>
#include <thread>
#include <chrono>

using AddFunc = int(*)(int, int);
using PowerFunc = double(*)(double, int);
using CircleAreaFunc = double(*)(double);
using MeanFunc = double(*)(const std::vector<double>&);

int main()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    void* library = dlopen("./lib/libmiptlib.dll", RTLD_LAZY);
    if (!library) {
        std::cerr << "Ошибка: " << dlerror() << std::endl;
        return 1;
    }
    
    auto add = (AddFunc)dlsym(library, "add");
    auto power = (PowerFunc)dlsym(library, "power");
    auto circleArea = (CircleAreaFunc)dlsym(library, "circleArea");
    auto mean = (MeanFunc)dlsym(library, "mean");
    
    std::cout << add(3, 4) << std::endl;
    std::cout << power(2, 5) << std::endl;
    std::cout << circleArea(5) << std::endl;
    
    std::vector<double> data = {1, 2, 3, 4, 5};
    std::cout << mean(data) << std::endl;
    
    dlclose(library);
}