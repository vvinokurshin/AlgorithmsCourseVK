/*
На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку поступления от 0.
Известно, что их все можно сложить один в один (то есть так, что каждый следующий помещается в предыдущий). 
Один ящик можно вложить в другой, если его можно перевернуть так, что размеры одного ящика по всем осям 
станут строго меньше размеров другого ящика по соответствующим осям.
Требуется определить, в какой последовательности они будут вложены друг в друга. Вывести номера ящиков.
Для сортировки точек реализуйте алгоритм сортировки вставками.
Максимальное кол-во 10000.
*/

#include <iostream>

template <class T, typename Comparator = std::less<T>>
void InsertionSort(T *arr, size_t size, Comparator cmp = Comparator())
{
    for (size_t i = 1; i < size; ++i)
    {
        T tmp = arr[i]; 
        size_t j = i - 1;

        for (; j >= 0 && cmp(tmp, arr[j]); --j)
        {
            arr[j + 1] = arr[j];
        }

        arr[j + 1] = tmp;
    }
}

struct Box
{
    size_t num;
    int a;
    int b;
    int c;
};

class BoxComparator
{
public:
    bool operator()(const Box &l, const Box &r)
    {
        int arr1[] = { l.a, l.b, l.c };
        int arr2[] = { r.a, r.b, r.c };

        InsertionSort(arr1, 3);
        InsertionSort(arr2, 3);

        return arr1[0] < arr2[0] && arr1[1] < arr2[1] && arr1[2] < arr2[2];
    }
};

void task(std::istream &input, std::ostream &output)
{
    int size = 0;
    input >> size;

    Box *arr = new Box[size];

    for (int i = 0; i < size; ++i)
    {
        arr[i].num = i;
        input >> arr[i].a >> arr[i].b >> arr[i].c;
    }

    InsertionSort(arr, size, BoxComparator());

    for (int i = 0; i < size; ++i)
    {
        output << arr[i].num << " ";
    }

    output << std::endl;

    delete[] arr;
}

int main()
{
    task(std::cin, std::cout);
    return 0;
}