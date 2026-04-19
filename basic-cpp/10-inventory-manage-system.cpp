/*
示例项目2：动态库存管理系统

需求分析：
创建一个程序，管理库存中的商品信息，
包括添加、删除、更新和显示商品。
每个商品包含商品ID、名称和数量。
*/

#include<iostream>
#include<vector>
#include<algorithm>


struct Product {
    int id;
    std::string name;
    int quantity;
};


int main()
{
    std::vector<Product> inventory;

    int choice;

    while (true)
    {
        std::cout << "=== Inventory Management System ===" << std::endl;
        std::cout << "1. Add Product" << std::endl;
        std::cout << "2. Remove Product" << std::endl;
        std::cout << "3. Update Product" << std::endl;
        std::cout << "4. Display All Products" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (choice == 1)
        {
            Product newProduct;
            std::cout << "Enter Product ID: ";
            std::cin >> newProduct.id;
            std::cout << "Enter Product Name: ";
            std::cin >> newProduct.name;
            std::cout << "Enter Product Quantity: ";
            std::cin >> newProduct.quantity;
            inventory.push_back(newProduct);
            std::cout << "Product added successfully!" << std::endl;
        }
        else if (choice == 2)
        {
            int id;
            std::cout << "Enter Product ID to remove: ";
            std::cin >> id;
            for (auto it = inventory.begin(); it != inventory.end(); ++it)
            {
                if (it->id == id)
                {
                    inventory.erase(it);
                    break;
                }
            }
            std::cout << "Product removed successfully!" << std::endl;
        }
        else if (choice == 3)
        {
            int id;
            std::cout << "Enter Product ID to update: ";
            std::cin >> id;
            for (auto& product : inventory)
            {
                if (product.id == id)
                {
                    // std::cout << "Enter new Product Name: ";
                    // std::cin >> product.name;
                    std::cout << "Enter new Product Quantity: ";
                    std::cin >> product.quantity;
                    break;
                }
            }
        }
        else if (choice == 4)
        {
            for (const auto& product : inventory)
            {
                std::cout << "ID: " << product.id
                          << ", Name: " << product.name
                          << ", Quantity: " << product.quantity << std::endl;
            }
        }
        else if (choice == 5)
        {
            std::cout << "Exited the system." << std::endl;
            break;
        }
    }

    return 0;

}