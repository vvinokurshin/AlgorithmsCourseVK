/*
Напишите функцию, проверяющую, что во всех узлах бинарного дерева поиска
хранится одинаковое значение. Значения - int.
*/

#include <iostream>
#include <stack>

template <typename T, typename Comparator = std::less<T>>
class BinaryTree {
    struct Node {
        explicit Node(const T &data)
            : data(data), left(nullptr), right(nullptr) {}

        T data;
        Node *left;
        Node *right;
    };

 public:
    BinaryTree();
    ~BinaryTree();

    bool find(const T &value);
    void add(const T &value);
    void remove(const T &value);
    bool inOrder() const;

 private:
    Node *root;
    Comparator cmp;

    Node *deleteNode(Node *node);
};

template <typename T, typename Comparator>
BinaryTree<T, Comparator>::BinaryTree() : root(nullptr), cmp(Comparator()) {}

template <typename T, typename Comparator>
BinaryTree<T, Comparator>::~BinaryTree() {
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
bool BinaryTree<T, Comparator>::find(const T &value) {
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
void BinaryTree<T, Comparator>::add(const T &value) {
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
void BinaryTree<T, Comparator>::remove(const T &value) {
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
typename BinaryTree<T, Comparator>::Node *
BinaryTree<T, Comparator>::deleteNode(Node *node) {
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
bool BinaryTree<T, Comparator>::inOrder() const {
    std::stack<Node *> s;

    Node *cur = root;
    T value = root->data;

    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }

        cur = s.top();
        s.pop();

        if (cur->data != value) {
            return false;
        }

        cur = cur->right;
    }

    return true;
}

void task(std::istream &input, std::ostream &output) {
    BinaryTree<int> tree;
    int cur = 0;

    while (input >> cur) {
        tree.add(cur);
    }

    output << tree.inOrder() << std::endl;
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}