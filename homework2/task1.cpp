/*
Реализуйте структуру данных типа “множество строк” на основе динамической
хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из
строчных латинских букв. Хеш-функция строки должна быть реализована с помощью
вычисления значения многочлена методом Горнера. Начальный размер таблицы должен
быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
когда коэффициент заполнения таблицы достигает 3/4. Структура данных должна
поддерживать операции добавления строки в множество, удаления строки из
множества и проверки принадлежности данной строки множеству.

1_2. Для разрешения коллизий используйте двойное хеширование.
*/

#include <iostream>
#include <vector>

enum HashTableNodeState { NIL, DEFAULT, DELETED };

template <typename T>
struct HashTableNode {
    HashTableNodeState state;
    T data;

    HashTableNode() : state(NIL) {}
    explicit HashTableNode(const T &data) : state(DEFAULT), data(data) {}
};

class StringHasher1 {
 public:
    StringHasher1(unsigned int prime = 71) : prime(prime) {}

    size_t operator()(const std::string &str) {
        size_t hash = 0;
        for (size_t i = 0; i < str.size(); i++) {
            hash = hash * prime + str[i];
        }
        return hash;
    }

 private:
    unsigned int prime;
};

class StringHasher2 {
 public:
    StringHasher2(unsigned int prime = 57) : prime(prime) {}

    size_t operator()(const std::string &str) {
        size_t hash = 0;
        for (size_t i = 0; i < str.size(); i++) {
            hash = hash * prime + str[i];
        }
        return hash;
    }

 private:
    unsigned int prime;
};

template <typename T, typename Hasher1, typename Hasher2>
class HashTable {
 private:
    static const size_t DefaultInitialSize = 8;
    const float maxFillFactor = 0.75;

 public:
    HashTable(const HashTable &other);
    HashTable(size_t initial_capacity = DefaultInitialSize)
        : table(initial_capacity), size(0) {}
    ~HashTable() = default;

    bool find(const T &key);
    bool add(const T &key);
    bool remove(const T &key);

 private:
    void grow();
    size_t doubleHash(const T &key, size_t ind, size_t tableSize);

    std::vector<HashTableNode<T>> table;
    size_t size;
    Hasher1 hasher1;
    Hasher2 hasher2;
};

template <typename T, typename Hasher1, typename Hasher2>
HashTable<T, Hasher1, Hasher2>::HashTable(const HashTable &other)
    : table(other.table), size(other.size) {}

template <typename T, typename Hasher1, typename Hasher2>
bool HashTable<T, Hasher1, Hasher2>::find(const T &key) {
    if (!size) {
        return false;
    }

    size_t ind = doubleHash(key, 0, table.size());

    for (size_t i = 0; i < table.size(); ++i) {
        if (table[ind].state == NIL) {
            return false;
        }

        if (table[ind].state == DEFAULT && table[ind].data == key) {
            return true;
        }

        ind = doubleHash(key, i + 1, table.size());
    }

    return false;
}

template <typename T, typename Hasher1, typename Hasher2>
bool HashTable<T, Hasher1, Hasher2>::add(const T &key) {
    if (size > maxFillFactor * table.size()) {
        grow();
    }

    size_t ind = doubleHash(key, 0, table.size());
    ssize_t indFirstDel = -1;

    for (size_t i = 0; i < table.size(); ++i) {
        if (table[ind].data == key && table[ind].state == DEFAULT) {
            return false;
        }

        if (table[ind].state == DELETED && indFirstDel < 0) {
            indFirstDel = ind;
        }

        if (table[ind].state == NIL) {
            if (indFirstDel < 0) {
                table[ind].data = key;
                table[ind].state = DEFAULT;
            } else {
                table[indFirstDel].data = key;
                table[indFirstDel].state = DEFAULT;
            }

            size++;
            return true;
        }

        ind = doubleHash(key, i + 1, table.size());
    }

    table[indFirstDel].data = key;
    table[indFirstDel].state = DEFAULT;
    size++;

    return true;
}

template <typename T, typename Hasher1, typename Hasher2>
bool HashTable<T, Hasher1, Hasher2>::remove(const T &key) {
    size_t ind = doubleHash(key, 0, table.size());

    for (size_t i = 0; i < table.size(); ++i) {
        if (table[ind].state == NIL) {
            return false;
        }

        if (table[ind].data == key && table[ind].state == DEFAULT) {
            table[ind].state = DELETED;
            size--;
            return true;
        }

        ind = doubleHash(key, i + 1, table.size());
    }

    return false;
}

template <typename T, typename Hasher1, typename Hasher2>
void HashTable<T, Hasher1, Hasher2>::grow() {
    std::vector<HashTableNode<T>> newTable(table.size() * 2);
    size_t newSize = 0;

    for (int i = 0; i < table.size(); ++i) {
        if (table[i].state == DEFAULT) {
            size_t ind = doubleHash(table[i].data, 0, newTable.size());

            for (int j = 0; j < newTable.size(); ++j) {
                if (newTable[ind].state == NIL) {
                    newTable[ind].data = table[i].data;
                    newTable[ind].state = DEFAULT;
                    newSize++;
                    break;
                }

                ind = doubleHash(table[i].data, j + 1, newTable.size());
            }
        }
    }

    size = newSize;
    table = std::move(newTable);
}
template <typename T, typename Hasher1, typename Hasher2>
size_t HashTable<T, Hasher1, Hasher2>::doubleHash(const T &key, size_t ind,
                                                  size_t tableSize) {
    return (hasher1(key) + ind * (hasher2(key) * 2 + 1)) % tableSize;
}

void task(std::istream &input, std::ostream &output) {
    HashTable<std::string, StringHasher1, StringHasher2> table;

    char mode;
    std::string key;

    while (input >> mode >> key) {
        switch (mode) {
        case '+':
            output << (table.add(key) ? "OK" : "FAIL") << std::endl;
            break;
        case '-':
            output << (table.remove(key) ? "OK" : "FAIL") << std::endl;
            break;
        case '?':
            output << (table.find(key) ? "OK" : "FAIL") << std::endl;
            break;
        }
    }
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}