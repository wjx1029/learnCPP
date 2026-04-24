//  map 算法 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/pd1xnld1n4mrvvy5#d2QTU

/*
使用AVL树来实现map（键值对映射）是一个高效的选择，特别适合需要频繁查找、插入和删除操作的场景
说明:
1. 平衡维护：在每次插入或删除后，都会更新节点的高度并计算平衡因子。如果某个节点的平衡因子超出了[-1, 1]范围，就需要通过旋转来重新平衡树。
2. 查找操作：由于AVL树的高度被保持在O(log n)，查找操作的时间复杂度为O(log n)。
3. 更新操作：如果插入的键已经存在，则更新其对应的值。
4. 遍历操作：中序遍历可以按键的顺序遍历所有键值对。
5. 内存管理：确保在析构函数中正确释放所有动态分配的内存，避免内存泄漏。
6. 泛型支持（可选）：为了使AVLMap更加通用，可以将其模板化，以支持不同类型的键和值。
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // 用于 std::max
#include <functional> // 用于 std::function

// 模板化AVL树节点结构
template <typename K, typename V>
struct AVLNode {
    K key;
    V value;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

// 获取节点高度
template <typename K, typename V>
int getHeight(AVLNode<K, V>* node) {
    return node ? node->height : 0;
}

// 计算平衡因子
template <typename K, typename V>
int getBalanceFactor(AVLNode<K, V>* node) {
    if (!node) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// 右旋转
/*
    y                             x
   / \                           / \
  x   T3            ==>          z   y
 / \                               / \
z   T2                            T2  T3
*/
template <typename K, typename V>
AVLNode<K, V>* rotateRight(AVLNode<K, V>* y) {
    AVLNode<K, V>* x = y->left;
    AVLNode<K, V>* T2 = x->right;
    // 执行旋转
    y->left = T2;
    x->right = y;
    // 更新高度
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    // 返回新的根节点
    return x;
}

// 左旋转
/*
    x                             y
   / \                           / \
  T1  y           ==>            x   z
     / \                       / \
    T2  z                     T1  T2
*/
template <typename K, typename V>
AVLNode<K, V>* rotateLeft(AVLNode<K, V>* x) {
    AVLNode<K, V>* y = x->right;
    AVLNode<K, V>* T2 = y->left;
    // 执行旋转
    x->right = T2;
    y->left = x;
    // 更新高度
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    // 返回新的根节点
    return y;
}

// 插入节点
template <typename K, typename V>
AVLNode<K, V>* insertNode(AVLNode<K, V>* node, const K& k, const V& v) {
    if (!node) {
        return new AVLNode<K, V>(k, v);
    }
    if (k < node->key) {
        node->left = insertNode(node->left, k, v);
    } else if (k > node->key) {
        node->right = insertNode(node->right, k, v);
    } else {
        node->value = v;
        return node;
    }
    // 更新高度
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    // 计算平衡因子
    int balance = getBalanceFactor(node);
    // 如果平衡因子超出[-1, 1]范围，需要通过旋转来重新平衡树
    // 左左旋转
    if (balance > 1 && k < node->left->key) {
        return rotateRight(node);
    }
    // 右右旋转
    if (balance < -1 && k > node->right->key) {
        return rotateLeft(node);
    }
    // 左右旋转
    if (balance > 1 && k > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // 右左旋转
    if (balance < -1 && k < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

// 查找节点
template <typename K, typename V>
V* searchNode(AVLNode<K, V>* node, const K& k) {
    if (node == nullptr) return nullptr;
    if (node->key == k) return &(node->value);
    if (k < node->key) return searchNode(node->left, k);
    return searchNode(node->right, k);
}

// 获取最小值
template <typename K, typename V>
AVLNode<K, V>* getMinNode(AVLNode<K, V>* node) {
    AVLNode<K, V>* minNode = node;
    while (minNode->left != nullptr) {
        minNode = minNode->left;
    }
    return minNode;
}

// 删除节点
template <typename K, typename V>
AVLNode<K, V>* deleteNode(AVLNode<K, V>* node, const K& k) {
    if (node == nullptr) return nullptr;
    if (k < node->key) {
        node->left = deleteNode(node->left, k);
    } else if (k > node->key) {
        node->right = deleteNode(node->right, k);
    } else {
        if ((node->left == nullptr) || (node->right == nullptr)) {
            AVLNode<K, V>* child = node->left != nullptr ? node->left : node->right;
            
            // 没有子节点
            if (child == nullptr) {
                child = node;
                node = nullptr;
            } else {    // 一个子节点
                *node = *child;
            }

            delete child;
        } else {
            // 有左右子节点，找到最小值节点，替换当前节点
            AVLNode<K, V>* minNode = getMinNode(node->right);
            node->key = minNode->key;
            node->value = minNode->value;
            node->right = deleteNode(node->right, minNode->key);
        }
    }

    if (node == nullptr) return node;

    // 更新高度
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    // 计算平衡因子
    int balance = getBalanceFactor(node);
    // 如果平衡因子超出[-1, 1]范围，需要通过旋转来重新平衡树
    // 左左旋转
    if (balance > 1 && k < node->left->key) {
        return rotateRight(node);
    }
    // 右右旋转
    if (balance < -1 && k > node->right->key) {
        return rotateLeft(node);
    }
    // 左右旋转
    if (balance > 1 && k > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // 右左旋转
    if (balance < -1 && k < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// 模板化的AVLMap类
template <typename K, typename V>
class AVLMap {
private:
    AVLNode<K, V>* root;

    // 中序遍历
    void inorderHelper(AVLNode<K, V>* node, std::vector<std::pair<K, V>>& result) const {
        if (node == nullptr) return;
        inorderHelper(node->left, result);
        result.emplace_back(node->key, node->value);
        inorderHelper(node->right, result);
    }

public:
    AVLMap() : root(nullptr) {}

    // 插入节点
    void put(const K& k, const V& v) {
        root = insertNode(root, k, v);
    }

    // 查找节点
    V* get(const K& k) const {
        return searchNode(root, k);
    }

    // 删除节点
    void remove(const K& k) {
        root = deleteNode(root, k);
    }

    // 中序遍历
    std::vector<std::pair<K, V>> inorderTraversal() const {
        std::vector<std::pair<K, V>> result;
        inorderHelper(root, result);
        return result;
    }

    // 析构函数
    ~AVLMap() {
        // 使用后序遍历释放节点
        std::function<void(AVLNode<K, V>*)> destroy = [&](AVLNode<K, V>* node) {
            if (node) {
                destroy(node->left);
                destroy(node->right);
                delete node;
            }
        };
        destroy(root);
    }
};


int main() {
    AVLMap<int, std::string> avlMap;

    // 插入键值对
    avlMap.put(10, "十");
    avlMap.put(20, "二十");
    avlMap.put(30, "三十");
    avlMap.put(40, "四十");
    avlMap.put(50, "五十");
    avlMap.put(25, "二十五");

    // 中序遍历
    std::vector<std::pair<int, std::string>> traversal = avlMap.inorderTraversal();
    std::cout << "中序遍历: ";
    for (const auto& pair : traversal) {
        std::cout << "(" << pair.first << ", \"" << pair.second << "\") ";
    }
    std::cout << std::endl;

    // 查找键
    std::string* val = avlMap.get(20);
    if (val)
        std::cout << "获取键20的值: " << *val << std::endl;
    else
        std::cout << "键20不存在。" << std::endl;

    val = avlMap.get(25);
    if (val)
        std::cout << "获取键25的值: " << *val << std::endl;
    else
        std::cout << "键25不存在。" << std::endl;

    val = avlMap.get(60);
    if (val)
        std::cout << "获取键60的值: " << *val << std::endl;
    else
        std::cout << "键60不存在。" << std::endl;

    // 删除键20
    avlMap.remove(20);
    std::cout << "删除键20后，中序遍历: ";
    traversal = avlMap.inorderTraversal();
    for (const auto& pair : traversal) {
        std::cout << "(" << pair.first << ", \"" << pair.second << "\") ";
    }
    std::cout << std::endl;

    return 0;
}