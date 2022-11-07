/*
ВНИМАНИЕ! Для решения данной задачи нужно использовать структуру данных стек!
Пара слов называется стековой анаграмой, если одно слово можно получить из другого, проведя 
последовательность стековых операций с его буквами (взять очередную букву исходного слова и
поместить ее в стек; взять букву из стека и добавить ее в конец выходного слова). Для заданной пары 
слов требуется определить, можно ли выполнить последовательность стековых операций, переводящую первое 
слово во второе. Все буквы в слове различные. Длина анаграммы ≤ 10000.
*/

#include <iostream>
#include <cassert>
#include <cstring>

class CArray
{
public:
    CArray() : buffer(0), bufferSize(0), realSize(0) {}
    CArray(size_t bufferSize);
    CArray(const CArray &arr);
    ~CArray() { delete[] buffer; }

    size_t Size() const { return realSize; }

    char GetAt(size_t index) const;
    char operator[](size_t index) const { return GetAt(index); }
    char &operator[](size_t index);
    CArray &operator=(const CArray arr);

    void Add(char element);
    void Remove(size_t index);

private:
    const size_t DefaultInitialSize = 10;
    char *buffer;
    size_t bufferSize;
    size_t realSize;

    void grow();
};

CArray::CArray(const CArray &arr)
{
    bufferSize = arr.bufferSize;
    realSize = arr.realSize;
    std::copy(arr.buffer, arr.buffer + arr.realSize, buffer);
}

char CArray::GetAt(size_t index) const
{
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}

char &CArray::operator[](size_t index)
{
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}

CArray &CArray::operator=(const CArray arr)
{
    bufferSize = arr.bufferSize;
    realSize = arr.realSize;
    std::copy(arr.buffer, arr.buffer + arr.realSize, buffer);

    return *this;
}

void CArray::grow()
{
    size_t newBufferSize = std::max(DefaultInitialSize, bufferSize * 2);
    char *newBuffer = new char[newBufferSize];

    std::copy(buffer, buffer + realSize, newBuffer);
    delete[] buffer;

    buffer = newBuffer;
    bufferSize = newBufferSize;
}

void CArray::Add(char element)
{
    if (realSize == bufferSize)
        grow();

    assert(realSize < bufferSize && buffer != 0);
    buffer[realSize++] = element;
}

void CArray::Remove(size_t index)
{
    assert(realSize > 0 && buffer != 0 && index >= 0 && index < realSize);

    if (index < realSize - 1)
        std::copy(buffer + index + 1, buffer + realSize, buffer + index);

    realSize--;
}

class Stack
{
public:
    Stack() : arr(), top(-1) {}
    ~Stack() {}

    void push(char a);
    char pop();
    char peek();

    bool IsEmpty() const { return top == -1; }

private:
    CArray arr;
    size_t top;
};

void Stack::push(char a)
{
    arr.Add(a);
    top++;
}

char Stack::pop()
{
    if (IsEmpty())
        return -1;

    char elem = arr[top];
    arr.Remove(top--);
    return elem;
}

char Stack::peek()
{
    if (IsEmpty())
        return -1;

    return arr[top];
}

void task(std::istream &input, std::ostream &output)
{
    Stack stack;
    std::string str1, str2;

    input >> str1;
    input >> str2;

    if (str1.length() != str2.length())
    {
        output << "NO" << std::endl;
        return;
    }

    int j = 0;
    for (int i = 0; i < str2.length(); ++i)
	{
		stack.push(str1[i]);
		while (stack.peek() == str2[j] && !stack.IsEmpty())
		{
		    stack.pop();
			j++;
		}
	}

	if (stack.IsEmpty()) 
        output << "YES" << std::endl;
	else 
        output << "NO" << std::endl;
}

int main()
{
    task(std::cin, std::cout);
    return 0;
}
