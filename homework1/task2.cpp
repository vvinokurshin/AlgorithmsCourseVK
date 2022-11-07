/*
2_2. Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m]
значения массива строго возрастают, а на интервале [m, n-1] строго убывают.
Найти m за O(log m). Требования:  Время работы O(log m). Внимание! В этой задаче
сначала нужно определить диапазон для бинарного поиска размером порядка m с
помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
*/

#include <cassert>
#include <iostream>

class CArray {
 public:
    CArray() : buffer(0), bufferSize(0), realSize(0) {}
    CArray(int bufferSize);
    CArray(const CArray &arr);
    ~CArray() { delete[] buffer; }

    int Size() const { return realSize; }

    int GetAt(int index) const;
    int operator[](int index) const { return GetAt(index); }
    int &operator[](int index);
    CArray &operator=(const CArray arr);

    void readArray(std::istream &input, size_t len);
    void writeArray(std::ostream &output);

    int exponentialSearch();
    int binarySearch(size_t startInd, size_t endInd);

    void Add(int element);

 private:
    const size_t DefaultInitialSize = 10;
    int *buffer;
    size_t bufferSize;
    size_t realSize;

    void grow();
};

CArray::CArray(const CArray &arr) {
    bufferSize = arr.bufferSize;
    realSize = arr.realSize;
    std::copy(arr.buffer, arr.buffer + arr.realSize, buffer);
}

int CArray::GetAt(int index) const {
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}

int &CArray::operator[](int index) {
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}

CArray &CArray::operator=(const CArray arr) {
    bufferSize = arr.bufferSize;
    realSize = arr.realSize;
    std::copy(arr.buffer, arr.buffer + arr.realSize, buffer);

    return *this;
}

void CArray::grow() {
    int newBufferSize = std::max(DefaultInitialSize, bufferSize * 2);
    int *newBuffer = new int[newBufferSize];

    std::copy(buffer, buffer + realSize, newBuffer);
    delete[] buffer;

    buffer = newBuffer;
    bufferSize = newBufferSize;
}

void CArray::Add(int element) {
    if (realSize == bufferSize)
        grow();

    assert(realSize < bufferSize && buffer != 0);
    buffer[realSize++] = element;
}

void CArray::readArray(std::istream &input, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        int cur_elem;
        input >> cur_elem;
        Add(cur_elem);
    }
}

void CArray::writeArray(std::ostream &output) {
    for (size_t i = 0; i < realSize; ++i)
        output << buffer[i] << " ";

    output << std::endl;
}

int CArray::binarySearch(size_t low, size_t high) {
    high += 1;

    while (low < high) {
        size_t mid = (low + high) / 2;

        if (buffer[mid] == buffer[low])
            return mid;
        if (buffer[mid] > buffer[mid - 1])
            low = mid;
        else
            high = mid;
    }

    return low;
}

int CArray::exponentialSearch() {
    size_t i = 1;

    while (i < realSize && buffer[i - 1] < buffer[i])
        i *= 2;

    return binarySearch(i / 2, std::min(i, realSize - 1));
}

void task(std::istream &input, std::ostream &output) {
    CArray arr;
    size_t len;

    std::cin >> len;

    arr.readArray(std::cin, len);

    std::cout << arr.exponentialSearch() << std::endl;
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}