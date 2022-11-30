/*
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤
K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции
сравнения снаружи.

2_1. Выведите элементы в порядке in-order (слева направо).
*/

#include <iostream>
#include <stack>

template <typename T, typename Comparator = std::less<T>>
class AVLTree {
    struct Node {
        explicit Node(const T &data)
            : data(data), left(nullptr), right(nullptr) {}

        T data;
        Node *left;
        Node *right;
    };

 public:
    AVLTree();
    ~AVLTree();

    bool find(const T &value);
    void add(const T &value);
    void remove(const T &value);
    void inOrder(std::ostream &output) const;

 private:
    Node *root;
    Comparator cmp;

    Node *deleteNode(Node *node);
};

template <typename T, typename Comparator>
AVLTree<T, Comparator>::AVLTree() : root(nullptr), cmp(Comparator()) {}

template <typename T, typename Comparator>
AVLTree<T, Comparator>::~AVLTree() {
    if (!root) {
        return;
    }

    std::stack<Node *> s;
    s.push(root);

    while (!s.empty()) {
        Node *node = s.top();
        s.pop();

        if (node->left) {
            s.push(node->left);
        }

        if (node->right) {
            s.push(node->right);
        }

        delete node;
    }
}

template <typename T, typename Comparator>
bool AVLTree<T, Comparator>::find(const T &value) {
    if (!root) {
        return false;
    }

    Node *cur = root;

    while (cur) {
        if (!cmp(value, cur->data) && !cmp(cur->data, value)) {
            return true;
        }

        if (cmp(value, cur->data)) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    return false;
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::add(const T &value) {
    if (!root) {
        root = new Node(value);
        return;
    }

    Node *cur = root, *parent = nullptr;

    while (cur) {
        parent = cur;

        if (cmp(value, cur->data)) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    if (!parent) {
        parent = root;
    }

    if (cmp(value, parent->data)) {
        parent->left = new Node(value);
    } else {
        parent->right = new Node(value);
    }
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::remove(const T &value) {
    if (!root) {
        return;
    }

    Node *cur = root, *parent = nullptr;

    while (cur) {
        if (!cmp(value, cur->data) && !cmp(cur->data, value)) {
            Node *replacedNode = deleteNode(cur);

            if (!parent) {
                root = replacedNode;
            } else if (parent->left == cur)
                parent->left = replacedNode;
            else if (parent->right == cur)
                parent->right = replacedNode;

            return;
        }

        parent = cur;

        if (cmp(value, cur->data)) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::deleteNode(Node *node) {
    if (!node->left) {
        Node *right = node->right;
        delete node;
        return right;
    } else if (!node->right) {
        Node *left = node->left;
        delete node;
        return left;
    } else {
        Node *minParent = node;
        Node *min = node->right;

        while (min->left) {
            minParent = min;
            min = min->left;
        }

        node->data = min->data;
        (minParent->left == min ? minParent->left : minParent->right) =
            min->right;

        delete min;
        return min;
    }
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::inOrder(std::ostream &output) const {
    std::stack<Node *> s;

    Node *cur = root;

    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }

        cur = s.top();
        s.pop();

        output << cur->data << " ";
        cur = cur->right;
    }

    output << std::endl;
}

void task(std::istream &input, std::ostream &output) {
    AVLTree<int> tree;
    size_t n = 0;
    int cur = 0;

    input >> n;

    for (int i = 0; i < n; ++i) {
        input >> cur;
        tree.add(cur);
    }

    tree.inOrder(output);
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}