/*
Реализовать очередь с помощью двух стеков.
Требования: Очередь должна быть реализована в виде класса. Стек тоже должен быть
реализован в виде класса.
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

    void Add(int element);
    void Remove(int index);

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

void CArray::Remove(int index) {
    assert(realSize > 0 && buffer != 0 && index >= 0 && index < realSize);

    if (index < realSize - 1)
        std::copy(buffer + index + 1, buffer + realSize, buffer + index);

    realSize--;
}

class Stack {
 public:
    Stack() : arr(), top(-1) {}
    ~Stack() {}

    void push(int a);
    int pop();

    bool IsEmpty() const { return top == -1; }

 private:
    CArray arr;
    size_t top;
};

void Stack::push(int a) {
    arr.Add(a);
    top++;
}

int Stack::pop() {
    if (IsEmpty())
        return -1;

    int elem = arr[top];
    arr.Remove(top--);
    return elem;
}

class Queue {
 public:
    Queue() : frontStack(), baskStack() {}
    ~Queue() {}

    void pushBack(int a);
    int popFront();
    bool IsEmpty() const { return size == 0; }

 private:
    Stack frontStack;
    Stack baskStack;
    size_t size;
};

void Queue::pushBack(int a) {
    baskStack.push(a);
    size++;
}

int Queue::popFront() {
    if (frontStack.IsEmpty())
        while (!baskStack.IsEmpty())
            frontStack.push(baskStack.pop());

    int elem = frontStack.pop();
    size--;
    return elem;
}

bool handler(Queue &q, int mode, int elem) {
    switch (mode) {
    case 2:
        if (q.IsEmpty())
            return elem == -1;

        return q.popFront() == elem;

    case 3:
        q.pushBack(elem);
        break;
    }

    return true;
}

void task(std::istream &input, std::ostream &output) {
    int len;
    input >> len;
    Queue q;

    for (int i = 0; i < len; ++i) {
        int mode, elem;
        input >> mode >> elem;

        if (!handler(q, mode, elem)) {
            output << "NO" << std::endl;
            return;
        }
    }

    output << "YES" << std::endl;
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}