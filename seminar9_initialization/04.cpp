#include <iostream>
#include <string>
#include <vector>
using std::cout, std::endl;
int main() {
    int* pInt = new int(123);
    cout << "int:" << *pInt << endl;
    delete pInt;
    
    std::string* pString = new std::string("Cats and Dogs");
    cout << "string:" << *pString << endl;
    delete pString;
    
    int* pIntArray = new int[5]{10, 20, 30, 40, 50};
    cout << "int array:";
    for (int i = 0; i < 5; ++i) {
        cout << pIntArray[i] << " ";
    }
    cout << endl;
    delete[] pIntArray;
    
    std::vector<int>* pVector = new std::vector<int>{10, 20, 30, 40, 50};
    cout << "vector:";
    for (int val : *pVector) {
        cout << val << " ";
    }
    cout << endl;
    delete pVector;
    
    std::string* pStringArray = new std::string[3]{"Cat", "Dog", "Mouse"};
    cout << "string array:";
    for (int i = 0; i < 3; ++i) {
        cout << pStringArray[i] << " ";
    }
    cout << endl;
    delete[] pStringArray;
    
}