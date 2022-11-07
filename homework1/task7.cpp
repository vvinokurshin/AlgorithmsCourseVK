/*
Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше
10^6. Отсортировать массив методом поразрядной сортировки LSD по байтам.
*/

#include <iostream>

int getByte(int64_t number, size_t numByte) {
    return number >> (8 * numByte) & 0xFF;
}

void LSDByteSort(int64_t *arr, size_t size, size_t numByte) {
    int min = getByte(arr[0], numByte), max = getByte(arr[0], numByte);

    for (size_t i = 1; i < size; ++i) {
        int byte = getByte(arr[i], numByte);
        min = std::min(byte, min);
        max = std::max(byte, max);
    }

    size_t counterSize = max - min + 1;
    int *counter = new int[counterSize]();

    for (size_t i = 0; i < size; ++i)
        counter[getByte(arr[i], numByte) - min]++;

    for (size_t i = 0; i < counterSize - 1; ++i)
        counter[i + 1] += counter[i];

    int64_t *tmp_arr = new int64_t[size];

    for (int i = size - 1; i >= 0; --i) {
        int position = getByte(arr[i], numByte) - min;
        tmp_arr[--counter[position]] = arr[i];
    }

    for (size_t i = 0; i < size; ++i)
        arr[i] = tmp_arr[i];

    delete[] tmp_arr;
    delete[] counter;
}

void LSDSort(int64_t *arr, size_t size) {
    for (size_t i = 0; i < 8; ++i)
        LSDByteSort(arr, size, i);
}

void task(std::istream &input, std::ostream &output) {
    size_t n = 0;
    input >> n;

    int64_t *arr = new int64_t[n];
    for (size_t i = 0; i < n; ++i)
        input >> arr[i];

    LSDSort(arr, n);

    for (size_t i = 0; i < n; ++i)
        output << arr[i] << " ";

    output << std::endl;

    delete[] arr;
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}