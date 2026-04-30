#include "mymath.h"
#include <iostream>

int main() {
    int sum_int = add_int(3, 4);
    float sum_float = add_float(3.5f, 4.2f);
    std::cout << "Sum (int): " << sum_int << std::endl;
    std::cout << "Sum (float): " << sum_float << std::endl;
    return 0;
}