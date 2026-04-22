// STL : https://www.yuque.com/lianlianfengchen-cvvh2/zack/ntwr3sees3bb5hg4


#include <iostream>

// 模拟实现一个简化版的 List
// 为了更好地理解 std::list 的内部工作原理，模拟实现一个简化版的双向链表

// List 类将包含以下组件：

// 1. 节点结构体（Node）：表示链表的每个节点。
// 2. 迭代器类（Iterator）：允许用户遍历链表。
// 3. List 类：管理链表的基本操作，如插入、删除和遍历。

// 节点结构体（Node）
template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(const T& value = T()) : data(value), prev(nullptr), next(nullptr) {}
};

// 迭代器类（Iterator）,支持 ++ 和 -- 操作。
template<typename T>
class List;

template <typename T>
class Iterator {
private:
    Node<T>* node_ptr;

    friend class List<T>;

public:
    using self_type = Iterator<T>;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    Iterator(Node<T>* node = nullptr) : node_ptr(node) {}

    // Dereference operator
    reference operator*() const { return node_ptr->data; }

    // Arrow operator
    pointer operator->() const { return &(node_ptr->data); }

    // Pre-increment operator
    self_type& operator++() { 
        if (node_ptr != nullptr)
        {
            node_ptr = node_ptr->next;
        }
        return *this;
     }

     // Post-increment operator
     self_type operator++(int) { 
        self_type temp = *this;
        ++(*this);
        return temp;
     }

     // Pre-decrement operator
     self_type& operator--() { 
        if (node_ptr != nullptr)
        {
            node_ptr = node_ptr->prev;
        }
        return *this;
     }

     // Post-decrement operator
     self_type operator--(int) { 
        self_type temp = *this;
        --(*this);
        return temp;
     }  

     // Equality operator
     bool operator==(const self_type& other) const { return node_ptr == other.node_ptr; }

     // Inequality operator
     bool operator!=(const self_type& other) const { return node_ptr != other.node_ptr; }

};

// List 类提供链表的基本功能。
template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    using iterator = Iterator<T>;
    using const_iterator = Iterator<T>;

    // 构造函数
    List() {
        head = new Node<T>();
        tail = new Node<T>();
        head->next = tail;
        tail->prev = head;
    }

    // 析构函数
    ~List() {
        clear();
        delete head;
        delete tail;
    }

    // 禁止复制构造函数和赋值运算符
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    // 插入元素到迭代器位置之前
    iterator insert(iterator pos, const T& value) {
        Node<T>* current = pos.node_ptr;
        Node<T>* new_node = new Node<T>(value);

        Node<T>* prev_node = current->prev;

        new_node->next = current;
        new_node->prev = prev_node;

        prev_node->next = new_node;
        current->prev = new_node;

        return iterator(new_node);
    }

    // 删除迭代器位置的元素
    iterator erase(iterator pos) {
        if (pos.node_ptr == head || pos.node_ptr == tail)
        {
            return pos;
        }
        Node<T>* temp = pos.node_ptr;
        pos.node_ptr->prev->next = pos.node_ptr->next;
        pos.node_ptr->next->prev = pos.node_ptr->prev;
        delete temp;
        return iterator(pos.node_ptr->next);
    }

    // 在链表头插入元素
    void push_front(const T& value) {
        insert(begin(), value);
    }

    // 在链表尾插入元素
    void push_back(const T& value) {
        insert(end(), value);
    }

    // 删除链表头元素
    void pop_front() {
        if (!empty())
        {
            erase(begin());
        }
    }

    // 删除链表尾元素
    void pop_back() {
        if (!empty())
        {
            iterator temp = end();
            --temp;
            erase(temp);
        }
    }

    // 获取头元素引用
    T& front() {
        return head->next->data;
    }

    // 获取尾元素引用
    T& back() {
        return tail->prev->data;
    }

    // 获取链表大小（O(n)复杂度）
    size_t size() const {
        size_t count = 0;
        for(auto it = begin(); it != end(); ++it) {
            ++count;
        }
        return count;
    }

    // 检查链表是否为空
    bool empty() const { return head->next == tail; }

    // 返回指向第一个元素的迭代器
    iterator begin() { return iterator(head->next); }

    // 返回指向最后一个元素的迭代器
    iterator end() { return iterator(tail); }

    // 清空链表
    void clear() {
        Node<T>* current = head->next;
        while(current != tail) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head->next = tail;
        tail->prev = head;
    }

    // 打印链表（辅助函数）
    void print() const {
        Node<T>* current = head->next;
        while(current != tail) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

};

// 测试代码
int main() {
    List<int> lst;

    // 插入元素
    lst.push_back(10);    // 链表: 10
    lst.push_front(5);    // 链表: 5, 10
    lst.push_back(15);    // 链表: 5, 10, 15
    lst.insert(++lst.begin(), 7); // 链表: 5, 7, 10, 15

    // 打印链表
    std::cout << "链表内容: ";
    lst.print(); // 输出: 5 7 10 15

    // 删除元素
    lst.pop_front(); // 链表: 7, 10, 15
    lst.pop_back();  // 链表: 7, 10

    // 打印链表
    std::cout << "删除头尾后链表内容: ";
    lst.print(); // 输出: 7 10

    // 插入和删除
    auto it = lst.begin();
    lst.insert(it, 3);  // 链表: 3, 7, 10
    lst.erase(++it);    // 链表: 3, 10

    // 打印链表
    std::cout << "插入和删除后链表内容: ";
    lst.print(); // 输出: 3 10

    // 清空链表
    lst.clear();
    std::cout << "清空后，链表是否为空: " << (lst.empty() ? "是" : "否") << std::endl;

    return 0;
}