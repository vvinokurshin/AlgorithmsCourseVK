/*
В каждой строке находится одна из следующих операций:
insert x — добавить в дерево ключ x. Если ключ x есть в дереве, то ничего делать
не надо. delete x — удалить из дерева ключ x. Если ключа x в дереве нет, то
ничего делать не надо. exists x — если ключ x есть в дереве, вывести «true»,
иначе «false» next x — минимальный элемент в дереве, больший x, или «none», если
такого нет. prev x — максимальный элемент в дереве, меньший x, или «none», если
такого нет.

Выведите последовательно результат выполнения всех операций exists, next, prev.
Следуйте формату выходного файла из примера.
*/

#include <iostream>
#include <stack>

template <typename T>
struct TreeValue {
    TreeValue() : exists(false), data(0) {}
    TreeValue(bool exists, T value) : exists(exists), data(value) {}
    TreeValue(const TreeValue &other)
        : exists(other.exists), data(other.data) {}

    TreeValue &operator=(const TreeValue &other);

    bool exists;
    T data;
};

template <typename T>
TreeValue<T> &TreeValue<T>::operator=(const TreeValue &other) {
    if (this != &other) {
        exists = other.exists;
        data = other.data;
    }

    return *this;
}

template <typename T, typename Comparator = std::less<T>>
class AVLTree {
    struct Node {
        explicit Node(const T &data)
            : data(data), left(nullptr), right(nullptr), height(1),
              numNodes(1) {}

        T data;
        Node *left;
        Node *right;
        size_t height;
        size_t numNodes;
    };

 public:
    AVLTree();
    ~AVLTree();

    void add(const T &value);
    void remove(const T &value);
    bool find(const T &value) const;
    TreeValue<T> next(const T &value) const;
    TreeValue<T> prev(const T &value) const;

 private:
    Node *root;
    Comparator cmp;

    size_t height(const Node *node) const;
    int balanceFactor(const Node *node) const;
    void fixHeight(Node *node);
    void fixNumNodes(Node *node);

    Node *leftRotate(Node *node);
    Node *rightRotate(Node *node);
    Node *balance(Node *node);

    Node *add(Node *node, const T &value);
    Node *remove(Node *node, const T &value);
    Node *removeMin(Node *node, Node *&min);
    bool find(Node *node, const T &value) const;
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

template <class T, class Comparator>
size_t AVLTree<T, Comparator>::height(const Node *node) const {
    if (node) {
        return node->height;
    }

    return 0;
}

template <class T, class Comparator>
int AVLTree<T, Comparator>::balanceFactor(const Node *node) const {
    return height(node->right) - height(node->left);
}

template <class T, class Comparator>
void AVLTree<T, Comparator>::fixHeight(Node *node) {
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

template <class T, class Comparator>
void AVLTree<T, Comparator>::fixNumNodes(Node *node) {
    node->numNodes = 1;

    if (node->left) {
        node->numNodes += node->left->numNodes;
    }

    if (node->right) {
        node->numNodes += node->right->numNodes;
    }
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::leftRotate(Node *node) {
    Node *right(node->right);
    node->right = right->left;
    right->left = node;

    fixHeight(node);
    fixNumNodes(node);
    fixHeight(right);
    fixNumNodes(right);

    return right;
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::rightRotate(Node *node) {
    Node *left(node->left);
    node->left = left->right;
    left->right = node;

    fixHeight(node);
    fixNumNodes(node);
    fixHeight(left);
    fixNumNodes(left);

    return left;
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::balance(Node *node) {
    fixHeight(node);
    fixNumNodes(node);

    int bFactor = balanceFactor(node);

    if (bFactor == 2) {
        if (balanceFactor(node->right) < 0) {
            node->right = rightRotate(node->right);
        }

        return leftRotate(node);
    }

    if (bFactor == -2) {
        if (balanceFactor(node->left) > 0) {
            node->left = leftRotate(node->left);
        }

        return rightRotate(node);
    }

    return node;
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::add(const T &value) {
    root = add(root, value);
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::add(Node *node, const T &value) {
    if (!node) {
        return new Node(value);
    }

    if (cmp(value, node->data)) {
        node->left = add(node->left, value);
    } else if (cmp(node->data, value)) {
        node->right = add(node->right, value);
    } else {
        return node;
    }

    return balance(node);
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::remove(const T &value) {
    root = remove(root, value);
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::remove(Node *node, const T &value) {
    if (!node) {
        return nullptr;
    }

    if (!cmp(value, node->data) && !cmp(node->data, value)) {
        Node *left = node->left, *right = node->right;

        delete node;

        if (!right) {
            return left;
        }

        Node *min = nullptr, *replacedNode = removeMin(right, min);
        min->right = replacedNode;
        min->left = left;

        return balance(min);
    }

    if (cmp(value, node->data)) {
        node->left = remove(node->left, value);
    } else {
        node->right = remove(node->right, value);
    }

    return balance(node);
}

template <typename T, typename Comparator>
bool AVLTree<T, Comparator>::find(const T &value) const {
    return find(root, value);
}

template <typename T, typename Comparator>
bool AVLTree<T, Comparator>::find(Node *node, const T &value) const {
    if (!node) {
        return false;
    }

    if (!cmp(node->data, value) && !cmp(value, node->data)) {
        return true;
    }

    if (cmp(value, node->data)) {
        return find(node->left, value);
    }

    return find(node->right, value);
}

template <typename T, typename Comparator>
TreeValue<T> AVLTree<T, Comparator>::next(const T &value) const {
    Node *cur = root, *succ = nullptr;

    while (cur != nullptr) {
        if (cur->data > value) {
            succ = cur;
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    if (succ) {
        return TreeValue(true, succ->data);
    }

    return TreeValue(false, 0);
}

template <typename T, typename Comparator>
TreeValue<T> AVLTree<T, Comparator>::prev(const T &value) const {
    Node *cur = root, *succ = nullptr;

    while (cur != nullptr) {
        if (cur->data < value) {
            succ = cur;
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }

    if (succ) {
        return TreeValue(true, succ->data);
    }

    return TreeValue(false, 0);
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::removeMin(Node *node, Node *&min) {
    if (!node->left) {
        min = node;
        return node->right;
    }

    node->left = removeMin(node->left, min);
    return balance(node);
}

void task(std::istream &input, std::ostream &output) {
    AVLTree<int> tree;

    std::string mode;
    int value = 0;
    TreeValue<int> res;

    while (input >> mode >> value) {
        switch (mode[0]) {
        case 'i':
            tree.add(value);
            break;
        case 'd':
            tree.remove(value);
            break;
        case 'e':
            if (tree.find(value)) {
                std::cout << "true" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }

            break;
        case 'n':
            res = tree.next(value);

            if (res.exists) {
                output << res.data << std::endl;
            } else {
                output << "none" << std::endl;
            }

            break;
        case 'p':
            res = tree.prev(value);

            if (res.exists) {
                output << res.data << std::endl;
            } else {
                output << "none" << std::endl;
            }

            break;
        }
    }
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}