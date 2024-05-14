#include "CustomArray.h"

CustomArray::CustomArray() : size(min_size), count(0), first(0), elems(new value_type[min_size]) {}

CustomArray::CustomArray(const CustomArray& other) : size(other.size), count(other.count), first(other.first), elems(new value_type[other.size]) {
    std::copy(other.elems, other.elems + other.size, elems);
}

CustomArray::~CustomArray() {
    delete[] elems;
}

CustomArray::iterator CustomArray::begin() {
    return elems + first;
}

CustomArray::iterator CustomArray::end() {
    return elems + first + count;
}

CustomArray::const_iterator CustomArray::cbegin() const {
    return elems + first;
}

CustomArray::const_iterator CustomArray::cend() const {
    return elems + first + count;
}

CustomArray::size_type CustomArray::getSize() const {
    return count;
}

CustomArray::size_type CustomArray::getCapacity() const {
    return size;
}

bool CustomArray::empty() const {
    return count == 0;
}

CustomArray::reference CustomArray::operator[](size_type index) {
    return elems[first + index];
}

CustomArray::const_reference CustomArray::operator[](size_type index) const {
    return elems[first + index];
}

CustomArray::reference CustomArray::front() {
    return elems[first];
}

CustomArray::const_reference CustomArray::front() const {
    return elems[first];
}

CustomArray::reference CustomArray::back() {
    return elems[first + count - 1];
}

CustomArray::const_reference CustomArray::back() const {
    return elems[first + count - 1];
}

void CustomArray::push_back(const value_type& value) {
    if (count == size) {
        reserve(size * 2);
    }
    elems[first + count] = value;
    count++;
}

void CustomArray::pop_back() {
    if (!empty()) {
        count--;
    }
}

void CustomArray::resize(size_type newSize) {
    if (newSize > size) {
        reserve(newSize);
    }
    count = std::min(count, newSize);
}

void CustomArray::reserve(size_type newCapacity) {
    if (newCapacity > size) {
        size = newCapacity;
        value_type* newElems = new value_type[size];
        std::copy(elems + first, elems + first + count, newElems);
        delete[] elems;
        elems = newElems;
        first = 0;
    }
}

void CustomArray::clear() {
    count = 0;
}


#include "CustomArray.h"

CustomArray CustomArray::createDynamicArray(const CustomArray::value_type* arr, CustomArray::size_type size, CustomArray::size_type& newSize) {
    if (size == 0) {
        newSize = 0;
        return CustomArray();
    }

    // Знаходимо найбільше число в масиві
    CustomArray::value_type maxElement = *std::max_element(arr, arr + size);

    // Створюємо масив результатів
    CustomArray resultArray;

    // Заповнюємо масив результатів різницями між вхідним масивом та квадратом найбільшого числа
    for (CustomArray::size_type i = 0; i < size; ++i) {
        resultArray.push_back(arr[i] - (maxElement * maxElement));
    }

    // Знаходимо суму всіх елементів масиву та середнє арифметичне їх модулів
    CustomArray::value_type sum = 0, sum2 = 0;
    for (CustomArray::size_type i = 0; i < size; ++i) {
        sum += resultArray[i];
        sum2 += abs(resultArray[i]);
    }

    // Додаємо суму та середнє арифметичне модулів в кінець масиву
    resultArray.push_back(sum);
    resultArray.push_back(sum2 / size);

    // Встановлюємо новий розмір масиву
    newSize = size + 2;

    return resultArray;
}




std::istream& operator>>(std::istream& input, CustomArray& arr) {
    for (CustomArray::size_type i = 0; i < arr.getSize(); ++i) {
        input >> arr[i];
    }   
    return input;
}

std::ostream& operator<<(std::ostream& output, const CustomArray& arr) {
    for (CustomArray::size_type i = 0; i < arr.getSize(); ++i) {
        output << arr[i] << " ";
    }
    return output;
}
