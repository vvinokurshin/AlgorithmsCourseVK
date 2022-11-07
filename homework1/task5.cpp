/*
На числовой прямой окрасили N отрезков. Известны координаты левого и правого
концов каждого отрезка (Li и Ri). Найти длину окрашенной части числовой прямой.
*/

#include <iostream>

template <class T, typename Comparator = std::less<T>>
void Merge(T *arr1, size_t len1, T *arr2, size_t len2, T *new_arr,
           Comparator cmp = Comparator()) {
    size_t i = 0, j = 0, k = 0;

    while (i < len1 && j < len2) {
        if (cmp(arr1[i], arr2[j]))
            new_arr[k++] = arr1[i++];
        else
            new_arr[k++] = arr2[j++];
    }

    while (i < len1)
        new_arr[k++] = arr1[i++];

    while (j < len2)
        new_arr[k++] = arr2[j++];
}

template <class T, typename Comparator = std::less<T>>
void MergeSort(T *arr, size_t len, Comparator cmp = Comparator()) {
    if (len <= 1)
        return;

    size_t firstLen = len / 2;
    size_t secondLen = len - firstLen;

    MergeSort(arr, firstLen, cmp);
    MergeSort(arr + firstLen, secondLen, cmp);
    T *new_arr = new T[len];
    Merge(arr, firstLen, arr + firstLen, secondLen, new_arr, cmp);
    std::copy(new_arr, new_arr + len, arr);
    delete[] new_arr;
}

enum TypePoint { in, out };

struct Point {
    int position;
    TypePoint type;
};

class SegmentComparator {
 public:
    bool operator()(const Point &l, const Point &r) {
        return l.position < r.position;
    }
};

void inputArr(Point *arr, size_t len, std::istream &input) {
    for (size_t i = 0; i < len; ++i) {
        input >> arr[i].position;

        if (i % 2 == 0)
            arr[i].type = in;
        else
            arr[i].type = out;
    }
}

int length(Point *arr, size_t len) {
    size_t res = 0, start = 0, width = 0;

    for (size_t i = 0; i < len; ++i) {
        if (arr[i].type == in) {
            width++;

            if (width == 1)
                start = arr[i].position;
        } else {
            width--;

            if (width == 0)
                res += arr[i].position - start;
        }
    }

    return res;
}

void task(std::istream &input, std::ostream &output) {
    size_t n = 0, len = 0;
    input >> n;
    len = n * 2;
    Point *arr = new Point[len];

    inputArr(arr, len, input);
    MergeSort(arr, len, SegmentComparator());

    output << length(arr, len) << std::endl;

    delete[] arr;
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}
