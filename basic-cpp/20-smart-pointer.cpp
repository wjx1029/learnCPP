// 智能指针 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/org4zwm7g8hpg4nm

#include <vector>
#include <iostream>
#include <memory>

class Test {
public:
    Test(int val) : value(val) {
        std::cout << "Test Constructor: " << value << std::endl;
    }
    ~Test() {
        std::cout << "Test Destructor: " << value << std::endl;
    }
    void show() const {
        std::cout << "Value: " << value << std::endl;
    }

private:
    int value;
};

class B; // 前向声明

class A {
public:
    std::shared_ptr<B> ptrB;

    A() { std::cout << "A Constructor" << std::endl; }
    ~A() { std::cout << "A Destructor" << std::endl; }
};

class B {
public:
    std::weak_ptr<A> ptrA; // 使用 weak_ptr

    B() { std::cout << "B Constructor" << std::endl; }
    ~B() { std::cout << "B Destructor" << std::endl; }
};

void demo()
{
    // std::unique_ptr 是一种独占所有权的智能指针，任何时刻只能有一个 unique_ptr 实例拥有对某个对象的所有权
    // ● 独占所有权：确保资源在一个所有者下。
    // ● 轻量级：没有引用计数，开销小。
    // ● 自动释放：在指针销毁时自动释放资源。
    {
        // 创建一个 unique_ptr
        std::unique_ptr<Test> ptr1(new Test(100));
        ptr1->show();

        // 使用 make_unique（C++14 引入）
        auto ptr2 = std::make_unique<Test>(200);
        ptr2->show();

        // 移动 unique_ptr
        std::unique_ptr<Test> ptr3 = std::move(ptr1);
        if (!ptr1) {
            std::cout << "ptr1 is now nullptr after move." << std::endl;
        }
        ptr3->show();

        // 重置 unique_ptr
        ptr2.reset(new Test(300));
        ptr2->show();
    }

    // std::shared_ptr 是一种共享所有权的智能指针，允许多个 shared_ptr 实例共享对同一个对象的所有权
    // ● 共享所有权：多个 shared_ptr 可以指向同一个对象。
    // ● 引用计数：跟踪有多少 shared_ptr 实例指向同一对象。
    // ● 自动释放：当引用计数为0时，自动释放资源
    {
        // 创建一个 shared_ptr
        std::shared_ptr<Test> sp1(new Test(100));
        std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;
        sp1->show();

        // 通过拷贝构造共享所有权
        std::shared_ptr<Test> sp2 = sp1;
        std::cout << "After sp2 = sp1:" << std::endl;
        std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;
        std::cout << "sp2 use_count: " << sp2.use_count() << std::endl;

        // 通过拷贝赋值共享所有权
        std::shared_ptr<Test> sp3;
        sp3 = sp2;
        std::cout << "After sp3 = sp2:" << std::endl;
        std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;
        std::cout << "sp2 use_count: " << sp2.use_count() << std::endl;
        std::cout << "sp3 use_count: " << sp3.use_count() << std::endl;

        // 重置 shared_ptr
        sp2.reset(new Test(200));
        std::cout << "After sp2.reset(new Test(200)):" << std::endl;
        std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;
        std::cout << "sp2 use_count: " << sp2.use_count() << std::endl;
        std::cout << "sp3 use_count: " << sp3.use_count() << std::endl;
        sp2->show();
        // 自动释放资源
        std::cout << "Exiting main..." << std::endl;
    }

    // std::weak_ptr 是一种不拥有对象所有权的智能指针，用于观察但不影响对象的生命周期。主要用于解决 shared_ptr 之间的循环引用问题
    // ● 非拥有所有权：不增加引用计数。
    // ● 可从 shared_ptr 生成：通过 std::weak_ptr 可以访问 shared_ptr 管理的对象。
    // ● 避免循环引用：适用于双向关联或观察者模式
    {
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();
        a->ptrB = b;
        b->ptrA = a;
    }
        std::cout << "Exiting main..." << std::endl;

    // weak_ptr 不能直接访问对象，需要通过 lock() 方法转换为 shared_ptr，并检查对象是否仍然存在
    {
        std::shared_ptr<int> sp = std::make_shared<int>(42);
        std::weak_ptr<int> wp = sp;

        if (auto locked = wp.lock()) { // 尝试获取 shared_ptr
            std::cout << "Value: " << *locked << std::endl;
        } else {
            std::cout << "Object no longer exists." << std::endl;
        }

        sp.reset(); // 释放资源

        if (auto locked = wp.lock()) { // 再次尝试获取 shared_ptr
            std::cout << "Value: " << *locked << std::endl;
        } else {
            std::cout << "Object no longer exists." << std::endl;
        }

    }
}

/*
最佳实践与常见陷阱:
选择合适的智能指针
● std::unique_ptr：
  ○ 用于明确的独占所有权场景。
  ○ 适用于资源的单一管理者或需要所有权转移的情况。
  ○ 更轻量，性能更优。
● std::shared_ptr：
  ○ 用于共享所有权的场景。
  ○ 需要多个指针共同管理同一资源时使用。
  ○ 引用计数带来一定的性能开销。
● std::weak_ptr：
  ○ 用于观察不拥有资源的场景。
  ○ 适用于需要避免循环引用或只需临时访问资源的情况。
● 使用 make_shared 与 make_unique
优先使用 make_shared 和 make_unique 来创建智能指针，避免直接使用 new，提高效率和异常安全性。
auto sp = std::make_shared<Test>(100);
auto up = std::make_unique<Test>(200);
*/

// Exercise

/*
练习题1：使用 std::unique_ptr 管理动态资源
题目描述：
编写一个C++类 ResourceManager，该类负责管理一个动态分配的整数资源。
使用 std::unique_ptr 来确保资源在 ResourceManager 对象销毁时被正确释放，从而避免内存泄漏。
*/

class ResourceManager {
private:
    std::unique_ptr<int> up;
public:
    ResourceManager(int x) {
        up = std::make_unique<int>(x);
    }

    int getValue() const {
        if (up) return *up;
        return -1;
    }

    void setValue(int newValue) {
        if (up) *up = newValue;
    } 

    ResourceManager(const ResourceManager&) = delete;

    ResourceManager& operator=(const ResourceManager&) = delete;

    ResourceManager(ResourceManager&& other) noexcept {
        up = std::move(other.up);
    }
    
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            up = std::move(other.up);
        }   
        return *this;
    }
};

void ex1()
{
    ResourceManager rm(100);
    std::cout << rm.getValue() << std::endl;
    rm.setValue(200);
    std::cout << rm.getValue() << std::endl;
    ResourceManager rm2 = std::move(rm);
    std::cout << rm.getValue() << std::endl;
    std::cout << rm2.getValue() << std::endl;
    ResourceManager rm3(400);
    std::cout << rm3.getValue() << std::endl;
    rm3 = std::move(rm2);
    std::cout << rm3.getValue() << std::endl;
}

/*
练习题2：使用 std::shared_ptr 和 std::weak_ptr 构建图的数据结构
题目描述：
设计并实现一个简单的图结构，其中每个节点可以连接到多个其他节点。
使用 std::shared_ptr 来管理节点之间的所有权关系，并使用 std::weak_ptr 防止循环引用，导致内存泄漏。
*/

class GraphNode {
public:
    int id;
    std::vector<std::weak_ptr<GraphNode>> ptrs;

    GraphNode(int i): id(i) {}

    void addEdge(const std::shared_ptr<GraphNode>& node) {
        std::cout << "addEdge " << id << " to " << node->id << std::endl;
        ptrs.push_back(node);
    }

    void printEdges() const {
        std::cout << "Node " << id << " " << "is connected to: ";
        for (auto p_node : ptrs) {
            if (auto locked = p_node.lock()) {
                std::cout << locked->id << ' ';
            }
        }
        std::cout << std::endl;
    }
};

std::vector<std::shared_ptr<GraphNode>> createGraph(int n, int e)
{
    std::vector<std::shared_ptr<GraphNode>> nodes;
    nodes.reserve(n);
    for (int i = 1; i <= n; i++)
    {
        auto sp_node = std::make_shared<GraphNode>(i);
        nodes.push_back(sp_node);
    }
    int x, y;
    while(e--)
    {
        if (!(std::cin >> x >> y)) break;
        // 增加边界检查更安全
        if (x > 0 && x <= n && y > 0 && y <= n) {
            nodes[x-1]->addEdge(nodes[y-1]);
            nodes[y-1]->addEdge(nodes[x-1]);
        }
    }
    return nodes;
}

void ex2()
{
    int n, e;
    std::cin >> n >> e;
    auto nodes = createGraph(n, e);
    for (int i = 0; i < n; i++)
    {
        nodes[i]->printEdges();
    }
}


int main()
{
    // demo();
    // ex1();
    ex2();
    return 0;
}