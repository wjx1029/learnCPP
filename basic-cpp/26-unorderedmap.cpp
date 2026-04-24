// 无序map : https://www.yuque.com/lianlianfengchen-cvvh2/zack/waeidxbas04tfy98

#include <vector>
#include <iostream>
#include <string>
#include <utility> // For std::pair
#include <functional> // For std::hash
#include <iterator> // For iterator_traits
#include <stdexcept> // For exceptions

// HashNode 用于存储键值对及相关的指针，以构建链表。每个 HashNode 包含键、值和指向下一个节点的指针。
template <typename K, typename V>
struct HashNode {
    std::pair<const K, V> data;
    HashNode* next;

    HashNode(const K& k, const V& v) : data(std::make_pair(k, v)), next(nullptr) {}
};

// MyHashMap 是我们自定义的哈希表实现，支持基本的 Map 操作和迭代器功能。
// 它使用一个向量（std::vector）来存储桶，每个桶是一个链表，用于处理冲突。
template <typename K, typename V, typename Hash = std::hash<K>>
class MyHashMap {
     // 迭代器类前向声明
    // class Iterator;
    // 类型定义
    using key_type = K;
    using mapped_type = V;
    using value_type = std::pair<const K, V>;
    using size_type = size_t;
private:
    std::vector<HashNode<K, V>*> buckets_;
    size_type bucket_count_;
    size_type element_count_;
    double max_load_factor_;
    Hash hash_func_;

    // 重新哈希，当负载因子超过最大负载因子时调用。
    void rehash();

public:
    // 构造函数
    MyHashMap(size_type initial_capacity = 16, double max_load_factor = 0.75);
    ~MyHashMap();

    // 禁止复制构造函数和赋值运算符
    MyHashMap(const MyHashMap&) = delete;
    MyHashMap& operator=(const MyHashMap&) = delete;

    // 基本操作
    void insert(const K& k, const V& v);
    V* find(const K& k);
    const V* find(const K& k) const;
    bool erase(const K& k);
    size_type size() const;
    bool empty() const;
    void clear();

    class Iterator {
    private:
        MyHashMap* map_;
        size_type bucket_index_;
        HashNode<K, V>* current_node_;

        // 移动到下一个节点
        void advance() ;
    
    public:
        // 迭代器别名
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const K, V>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        // 构造函数
        Iterator(MyHashMap* map, size_type bucket_index, HashNode<K, V>* node);
        
        // 解引用运算符
        reference operator*() const;
        pointer operator->() const;

        // 指向下一个元素的迭代器
        Iterator& operator++();
        Iterator operator++(int);

        // 比较运算符
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    };

    // 迭代器操作
    Iterator begin();
    Iterator end();

};


// 构造函数及析构函数
template <typename K, typename V, typename Hash>
MyHashMap<K, V, Hash>::MyHashMap(size_type initial_capacity, double max_load_factor)
    : bucket_count_(initial_capacity), 
      element_count_(0), 
      max_load_factor_(max_load_factor), 
      hash_func_(Hash()) {
    buckets_.resize(bucket_count_, nullptr);
}

template <typename K, typename V, typename Hash>
MyHashMap<K, V, Hash>::~MyHashMap() {
    clear();
}

// 插入
template <typename K, typename V, typename Hash>
void MyHashMap<K, V, Hash>::insert(const K& k, const V& v) {
    size_type hash_value = hash_func_(k);
    size_type bucket_index = hash_value % bucket_count_;

    HashNode<K, V>* node = buckets_[bucket_index];
    while(node != nullptr) {
        if(node->data.first == k) {
            node->data.second = v;
            return;
        }
        node = node->next;
    }

    node = new HashNode<K, V>(k, v);
    node->next = buckets_[bucket_index];
    buckets_[bucket_index] = node;
    element_count_++;

    double load_factor = static_cast<double>(element_count_) / bucket_count_;
    if(load_factor > max_load_factor_) {
        rehash();
    }
}

// 查找
template <typename K, typename V, typename Hash>
V* MyHashMap<K, V, Hash>::find(const K& k) {
    size_type hash_value = hash_func_(k);
    size_type bucket_index = hash_value % bucket_count_;
    // std::cout << "ing.."<< std::endl;
    HashNode<K, V>* node = buckets_[bucket_index];
    while(node != nullptr) {
        if(node->data.first == k) {
            return &(node->data.second);
        }
        node = node->next;
    }
    return nullptr;
}

// 查找const
template <typename K, typename V, typename Hash>
const V* MyHashMap<K, V, Hash>::find(const K& k) const {
    size_type hash_value = hash_func_(k);
    size_type bucket_index = hash_value % bucket_count_;
    // std::cout << "ing.."<< std::endl;
    HashNode<K, V>* node = buckets_[bucket_index];
    while(node != nullptr) {
        if(node->data.first == k) {
            return &(node->data.second);
        }
        node = node->next;
    }
    return nullptr;
}


// 根据键删除对应的键值对，返回删除是否成功。
template <typename K, typename V, typename Hash>
bool MyHashMap<K, V, Hash>::erase(const K& k) {
    size_type hash_value = hash_func_(k);
    size_type bucket_index = hash_value % bucket_count_;

    HashNode<K, V>* node = buckets_[bucket_index];
    HashNode<K, V>* prev = nullptr;

    while(node != nullptr) {
        if(node->data.first == k) {
            if(prev == nullptr) {
                buckets_[bucket_index] = node->next;
            } else {
                prev->next = node->next;
            }
            delete node;
            element_count_--;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

// 删除哈希表中的所有元素，释放内存。
template <typename K, typename V, typename Hash>
void MyHashMap<K, V, Hash>::clear() {
    for(size_type i = 0; i < bucket_count_; ++i) {
        HashNode<K, V>* node = buckets_[i];
        while(node != nullptr) {
            HashNode<K, V>* next = node->next;
            delete node;
            node = next;
        }
        buckets_[i] = nullptr;
    }
    element_count_ = 0;
}

// 当负载因子超过阈值时，扩展哈希表容量并重新分配所有元素。
template <typename K, typename V, typename Hash>
void MyHashMap<K, V, Hash>::rehash() {
    size_type new_bucket_count = bucket_count_ * 2;
    std::vector<HashNode<K, V>*> new_buckets(new_bucket_count, nullptr);

    for(size_type i = 0; i < bucket_count_; ++i) {
        HashNode<K, V>* node = buckets_[i];
        while(node != nullptr) {
            HashNode<K, V>* next_node = node->next;
            size_type new_bucket_index = hash_func_(node->data.first) % new_bucket_count;

            node->next = new_buckets[new_bucket_index];
            new_buckets[new_bucket_index] = node;
            
            node = next_node;
        }
    }

    buckets_ = std::move(new_buckets);
    bucket_count_ = new_bucket_count;
}

// 获取大小和状态
template <typename K, typename V, typename Hash>
typename MyHashMap<K, V, Hash>::size_type MyHashMap<K, V, Hash>::size() const {
    return element_count_;
}

template <typename K, typename V, typename Hash>
bool MyHashMap<K, V, Hash>::empty() const {
    return element_count_ == 0;
}


// Iterator 类实现

// Iterator 构造函数
template <typename K, typename V, typename Hash>
MyHashMap<K, V, Hash>::Iterator::Iterator(MyHashMap* map, size_type bucket_index, HashNode<K, V>* node)
    : map_(map), bucket_index_(bucket_index), current_node_(node) {}

// 解引用操作符
template <typename K, typename V, typename Hash>
typename MyHashMap<K, V, Hash>::Iterator::reference 
MyHashMap<K, V, Hash>::Iterator::operator*() const {
    if(current_node_ == nullptr) {
        throw std::out_of_range("Iterator is at end of map");
    }
    return current_node_->data;
}

// 成员访问操作符
template <typename K, typename V, typename Hash>
typename MyHashMap<K, V, Hash>::Iterator::pointer 
MyHashMap<K, V, Hash>::Iterator::operator->() const {
    if(current_node_ == nullptr) {
        throw std::out_of_range("Iterator is at end of map");
    }
    return &(current_node_->data);
}

// 前置递增操作符
template <typename K, typename V, typename Hash>
typename MyHashMap<K, V, Hash>::Iterator&
MyHashMap<K, V, Hash>::Iterator::operator++() {    
    advance();
    return *this;
}

// 后置递增操作符
template <typename K, typename V, typename Hash>
typename MyHashMap<K, V, Hash>::Iterator
MyHashMap<K, V, Hash>::Iterator::operator++(int) {
    Iterator temp = *this;
    advance();
    return temp;
}

// 等价操作符
template <typename K, typename V, typename Hash>
bool MyHashMap<K, V, Hash>::Iterator::operator==(const Iterator& other) const {
    return map_ == other.map_ && bucket_index_ == other.bucket_index_ && current_node_ == other.current_node_;
}

// 不等价操作符
template <typename K, typename V, typename Hash>
bool MyHashMap<K, V, Hash>::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

// advance 函数：移动到下一个有效节点
template <typename K, typename V, typename Hash>
void MyHashMap<K, V, Hash>::Iterator::advance() {
    // 1. 当前链表内移动
    if (current_node_ != nullptr) {
        current_node_ = current_node_->next;
    }

    // 2. 如果链表结束 → 找下一个非空桶
    while (current_node_ == nullptr && bucket_index_ + 1 < map_->bucket_count_) {
        bucket_index_++;
        current_node_ = map_->buckets_[bucket_index_];
    }

    // 3. 如果所有桶都为空，返回 end()
    if (current_node_ == nullptr) {
        bucket_index_ = map_->bucket_count_;
    }
}


// begin() 函数：返回指向第一个元素的迭代器
template <typename K, typename V, typename Hash>
typename MyHashMap<K, V, Hash>::Iterator 
MyHashMap<K, V, Hash>::begin() {
    for (size_type i = 0; i < bucket_count_; ++i) {
        if (buckets_[i] != nullptr) {
            return Iterator(this, i, buckets_[i]);
        }
    }
    return end();
}

// end() 函数：返回指向最后一个元素的迭代器
template <typename K, typename V, typename Hash>
typename MyHashMap<K, V, Hash>::Iterator 
MyHashMap<K, V, Hash>::end() {
    return Iterator(this, bucket_count_, nullptr);
}




int main() {
    MyHashMap<std::string, int> myMap;

    // 插入元素
    myMap.insert("apple", 3);
    myMap.insert("banana", 5);
    myMap.insert("orange", 2);
    myMap.insert("grape", 7);
    myMap.insert("cherry", 4);

    // 使用迭代器遍历元素
    std::cout << "Map contents:\n";
    for(auto it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << it->first << " => " << it->second << "\n";
    }

    // 查找元素
    std::string keyToFind = "banana";
    int* value = myMap.find(keyToFind);
    if(value != nullptr) {
        std::cout << "\nFound " << keyToFind << " with value: " << *value << "\n";
    } else {
        std::cout << "\n" << keyToFind << " not found.\n";
    }

    // 删除元素
    myMap.erase("apple");
    myMap.erase("cherry");

    // 再次遍历
    std::cout << "\nAfter erasing apple and cherry:\n";
    for(auto it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << it->first << " => " << it->second << "\n";
    }

    return 0;
}