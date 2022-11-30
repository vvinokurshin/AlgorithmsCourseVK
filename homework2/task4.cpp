/*
4_2. Порядковые статистики
Дано число N и N строк. Каждая строка содержит команду добавления или удаления
натуральных чисел, а также запрос на получение k-ой порядковой статистики.
Команда добавления числа A задается положительным числом A, команда удаления
числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой
статистики задается числом k.
Требования: скорость выполнения запроса - O(log n).
*/

#include <iostream>
#include <stack>

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
    T kth_stat(const size_t &k);

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

    T kth_stat(Node *node, const size_t &k);
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
    } else {
        node->right = add(node->right, value);
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
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::removeMin(Node *node, Node *&min) {
    if (!node->left) {
        min = node;
        return node->right;
    }

    node->left = removeMin(node->left, min);
    return balance(node);
}

template <typename T, typename Comparator>
T AVLTree<T, Comparator>::kth_stat(const size_t &k) {
    return kth_stat(root, k + 1);
}

template <typename T, typename Comparator>
T AVLTree<T, Comparator>::kth_stat(Node *node, const size_t &k) {
    size_t numLeft = node->left ? node->left->numNodes : 0;
    size_t numRight = node->right ? node->right->numNodes : 0;
    size_t curStat = node->numNodes - numRight;

    if (k < curStat) {
        return kth_stat(node->left, k);
    }

    if (k > curStat) {
        return kth_stat(node->right, k - numLeft - 1);
    }

    return node->data;
}

void task(std::istream &input, std::ostream &output) {
    AVLTree<int> tree;
    size_t n = 0;
    input >> n;

    size_t cur_k = 0;
    int cur_value = 0;

    for (size_t i = 0; i < n; i++) {
        input >> cur_value >> cur_k;

        if (cur_value < 0) {
            tree.remove(-cur_value);
        } else {
            tree.add(cur_value);
        }

        output << tree.kth_stat(cur_k) << " ";
    }

    output << std::endl;
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}