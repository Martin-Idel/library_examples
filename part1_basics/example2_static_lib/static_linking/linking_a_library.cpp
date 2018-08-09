#include <iostream>
#include <string>

#include "first_library/first_library.hpp"

int main() {
    std::cout << std::to_string(my_lib::addingTwoNumbers(10, 20)) << std::endl;
    return 0;
}