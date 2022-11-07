/*
Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор
пользователя, посещаемость сайта). Напишите программу, которая выбирает K
пользователей, которые чаще других заходили на сайт, и выводит их в порядке
возрастания посещаемости. Количество заходов и идентификаторы пользователей не
повторяются. Требования: время работы O(N * logK), где N - кол-во пользователей.
Ограничение на размер кучи O(K). Формат входных данных: Сначала вводятся N и K,
затем пары (Идентификатор пользователя, посещаемость сайта). Формат выходных
данных: Идентификаторы пользователей в порядке возрастания посещаемости
*/

#include <cassert>
#include <iostream>

template <class T> class CArray {
 public:
    CArray() : buffer(0), bufferSize(0), realSize(0) {}
    CArray(size_t bufferSize);
    CArray(const CArray &arr);
    ~CArray() { delete[] buffer; }

    size_t Size() const { return realSize; }

    T GetAt(size_t index) const;
    T operator[](size_t index) const { return GetAt(index); }
    T &operator[](size_t index);
    CArray &operator=(const CArray arr);

    bool IsEmpty() const { return realSize == 0; }
    T getLast() { return buffer[realSize - 1]; }
    void deleteLast() { --realSize; }

    void Add(T element);

 private:
    const size_t DefaultInitialSize = 10;
    T *buffer;
    size_t bufferSize;
    size_t realSize;

    void grow();
};

template <class T> CArray<T>::CArray(const CArray<T> &arr) {
    bufferSize = arr.bufferSize;
    realSize = arr.realSize;
    std::copy(arr.buffer, arr.buffer + arr.realSize, buffer);
}

template <class T> T CArray<T>::GetAt(size_t index) const {
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}

template <class T> T &CArray<T>::operator[](size_t index) {
    assert(index < realSize && buffer != 0);
    return buffer[index];
}

template <class T> CArray<T> &CArray<T>::operator=(const CArray<T> arr) {
    bufferSize = arr.bufferSize;
    realSize = arr.realSize;
    std::copy(arr.buffer, arr.buffer + arr.realSize, buffer);

    return *this;
}

template <class T> void CArray<T>::grow() {
    size_t newBufferSize = std::max(DefaultInitialSize, bufferSize * 2);
    T *newBuffer = new T[newBufferSize];

    std::copy(buffer, buffer + realSize, newBuffer);
    delete[] buffer;

    buffer = newBuffer;
    bufferSize = newBufferSize;
}

template <class T> void CArray<T>::Add(T element) {
    if (realSize == bufferSize)
        grow();

    assert(realSize < bufferSize && buffer != 0);
    buffer[realSize++] = element;
}

template <class T, class Comparator> class MinHeap {
 public:
    MinHeap() : arr() {}
    ~MinHeap() {}

    void Insert(T elem);
    T extractMin();
    T peekMin() const;

 private:
    CArray<T> arr;
    Comparator cmp;

    void siftDown(size_t ind);
    void siftUp(size_t ind);

    size_t parent(size_t ind) { return (ind - 1) / 2; }
    size_t left(size_t ind) { return 2 * ind + 1; }
    size_t right(size_t ind) { return 2 * ind + 2; }
};

template <class T, class Comparator>
void MinHeap<T, Comparator>::siftDown(size_t ind) {
    size_t smallest = ind;
    size_t left_ind = left(ind), right_ind = right(ind);

    if (left_ind < arr.Size() && cmp(arr[left_ind], arr[ind]))
        smallest = left_ind;

    if (right_ind < arr.Size() && cmp(arr[right_ind], arr[smallest]))
        smallest = right_ind;

    if (smallest != ind) {
        std::swap(arr[ind], arr[smallest]);
        siftDown(smallest);
    }
}

template <class T, class Comparator>
void MinHeap<T, Comparator>::siftUp(size_t ind) {
    while (ind > 0) {
        size_t parent_ind = parent(ind);

        if (!cmp(arr[ind], arr[parent_ind]))
            return;

        std::swap(arr[ind], arr[parent_ind]);
        ind = parent_ind;
    }
}

template <class T, class Comparator> void MinHeap<T, Comparator>::Insert(T el) {
    arr.Add(el);
    siftUp(arr.Size() - 1);
}

template <class T, class Comparator> T MinHeap<T, Comparator>::extractMin() {
    assert(!arr.IsEmpty());

    T result = arr[0];
    arr[0] = arr.getLast();
    arr.deleteLast();

    if (!arr.IsEmpty())
        siftDown(0);

    return result;
}

template <class T, class Comparator> T MinHeap<T, Comparator>::peekMin() const {
    assert(!arr.IsEmpty());
    return arr[0];
}

struct User {
    int id;
    int count;
};

class UserComparator {
 public:
    bool operator()(const User &l, const User &r) { return l.count < r.count; }
};

void topKUsers(std::istream &input, std::ostream &output) {
    size_t n, k;
    MinHeap<User, UserComparator> heap;
    User cur_user;

    input >> n >> k;

    for (size_t i = 0; i < k; ++i) {
        input >> cur_user.id >> cur_user.count;
        heap.Insert(cur_user);
    }

    for (size_t i = k; i < n; ++i) {
        input >> cur_user.id >> cur_user.count;
        heap.Insert(cur_user);
        heap.extractMin();
    }

    for (size_t i = 0; i < k; ++i) {
        cur_user = heap.extractMin();
        output << cur_user.id << " ";
    }

    output << std::endl;
}

int main(void) {
    topKUsers(std::cin, std::cout);
    return 0;
}