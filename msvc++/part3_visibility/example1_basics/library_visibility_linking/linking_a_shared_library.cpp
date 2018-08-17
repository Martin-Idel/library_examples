#include <iostream>
#include <string>

#include "library_visibility/visible_library.hpp"

int main() {
    std::cout << std::to_string(my_lib_visibility::computeNchooseK(6, 4)) << std::endl;
    std::cout << std::to_string(my_lib_visibility::factorial(10)) << std::endl;
    std::cout << my_lib_visibility::random_number << std::endl;
    return 0;
}