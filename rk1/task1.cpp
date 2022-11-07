/*
Дан отсортированный по возрастанию массив попарно различных целых чисел A[0..n-1]. 
На вход также подается некоторое целое число k. Необходимо вернуть индекс элемента k в массиве A, 
если он там присутствует, либо вернуть позицию, куда его следовало бы вставить, чтобы массив остался отсортированным.
Требование: сложность O(logN)
*/

#include <iostream>

int FindInsertionPoint(const int *arr, size_t count, int element)
{
    size_t first = 0;
    size_t last = count;

    while (first < last)
    {
        size_t mid = (first + last) / 2;
        
        if (arr[mid] < element)
            first = mid + 1;
        else
            last = mid;
    }

    return first;
}

void task(std::istream &input, std::ostream &output)
{
    size_t size = 0;
    input >> size;

    int *arr = new int[size];

    for (int i = 0; i < size; ++i)
        input >> arr[i];

    int k = 0;
    input >> k;

    output << FindInsertionPoint(arr, size, k) << std::endl;

    delete[] arr; 
}

int main()
{
    task(std::cin, std::cout);
    return 0;
}