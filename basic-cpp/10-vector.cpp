// vector用法 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/xgsbx98y2m9ydkq1

#include <iostream>
#include <vector>

int main() {
    
    // 使用 reserve() 可以提前为向量分配足够的内存，减少内存重新分配的次数，提高性能。
    {
        std::vector<int> vec;
    
        // 预留空间
        vec.reserve(1000);
        std::cout << "Capacity after reserve(1000): " << vec.capacity() << std::endl;
        std::cout << "Size before adding elements: " << vec.size() << std::endl;
        
        // 添加元素
        for(int i = 0; i < 1000; ++i) {
            vec.push_back(i);
        }
        
        std::cout << "Size after adding elements: " << vec.size() << std::endl;
        std::cout << "Capacity after adding elements: " << vec.capacity() << std::endl;
    }

    // 使用 shrink_to_fit() 可以请求向量释放未使用的内存，减少内存占用。
    {
            std::vector<int> vec;
    
        // 预留较大的空间
        vec.reserve(1000);
        std::cout << "Size before shrink_to_fit: " << vec.size() << std::endl;
        std::cout << "Capacity before shrink_to_fit: " << vec.capacity() << std::endl;

        // 添加少量元素
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        
        // 请求释放未使用的内存
        vec.shrink_to_fit();
        
        std::cout << "Size after shrink_to_fit: " << vec.size() << std::endl;
        std::cout << "Capacity after shrink_to_fit: " << vec.capacity() << std::endl;
    }

    return 0;
}