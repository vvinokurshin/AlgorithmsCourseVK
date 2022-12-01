/*
Нужно кастомизировать std::unordered_set для операций со структурой данных
struct Node {
    std::string product_name;
    int color;
    int size;
};
*/

#include <iostream>
#include <unordered_set>

struct Node {
    std::string product_name;
    int color;
    int size;
};

namespace std {
template <>
struct hash<Node> {
    size_t operator()(const Node &key) const {
        size_t hash = 0;
        for (size_t i = 0; i < key.product_name.length(); ++i)
            hash = hash * 71 + key.product_name[i];
        return hash;
    }
};
} // namespace std

bool operator==(const Node first, const Node second) {
    return first.product_name == second.product_name &&
           first.color == second.color && first.size == second.size;
}

void task(std::istream &input, std::ostream &output) {
    std::unordered_set<Node> table;
    Node cur;
    char mode;

    while (input >> mode >> cur.product_name >> cur.color >> cur.size) {
        switch (mode) {
        case '+':
            output << (table.insert(cur).second ? "OK" : "FAIL") << std::endl;
            break;
        case '-':
            output << (table.erase(cur) ? "OK" : "FAIL") << std::endl;
            break;
        case '?':
            output << (table.find(cur) != table.end() ? "OK" : "FAIL")
                   << std::endl;
            break;
        }
    }
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}