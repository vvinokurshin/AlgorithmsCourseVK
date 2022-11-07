/*
Дано множество целых чисел из [0..10^9] размера n.
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие
параметры множества: 1) 10%  перцентиль 2) медиана 3) 90%  перцентиль Реализуйте
стратегию выбора опорного элемента “случайный элемент”. Функцию Partition
реализуйте методом прохода двумя итераторами от конца массива к началу.
*/

#include <iostream>

template <class T, typename Comparator = std::less<T>>
int partition(T *arr, size_t l, size_t r, Comparator cmp = Comparator()) {
    size_t pivot_idx = l + rand() % (r - l);
    T pivot = arr[pivot_idx];

    std::swap(arr[pivot_idx], arr[l]);

    int i = r - 1, j = r - 1;

    while (i != l) {
        if (cmp(arr[i], pivot))
            i--;
        else
            std::swap(arr[i--], arr[j--]);
    }

    std::swap(arr[j], arr[l]);

    return j;
}

template <class T, typename Comparator = std::less<T>>
T kth_stat(T *arr, size_t size, size_t k, Comparator cmp = Comparator()) {
    size_t l = 0, r = size;

    while (l < r) {
        size_t m = partition(arr, l, r, cmp);

        if (m == k)
            return arr[k];

        if (m < k)
            l = m + 1;
        else
            r = m;
    }
}

void task(std::istream &input, std::ostream &output) {
    size_t n = 0;
    input >> n;

    int *arr = new int[n];
    for (size_t i = 0; i < n; ++i)
        input >> arr[i];

    output << kth_stat(arr, n, n / 10) << std::endl;
    output << kth_stat(arr, n, n / 2) << std::endl;
    output << kth_stat(arr, n, 9 * n / 10) << std::endl;

    delete[] arr;
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}