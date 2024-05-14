#include "CustomArray.h"
#include <iostream>
#include <ctime>

int main() {
    const CustomArray::size_type size = 5;
    CustomArray::value_type initialArray[size]{};

    srand(time(0));
    std::cout << "Initial Array: ";
    for (CustomArray::size_type i = 0; i < size; ++i) {
        initialArray[i] = rand() % 101 - 50;
        std::cout << initialArray[i] << " ";
    }
    std::cout << std::endl;

    CustomArray arr;
    CustomArray::size_type newSize = 0;
    CustomArray resultArray = arr.createDynamicArray(initialArray, size, newSize);

    std::cout << "Result Array: ";
    for (CustomArray::size_type i = 0; i < newSize; ++i) {
        std::cout << resultArray[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}