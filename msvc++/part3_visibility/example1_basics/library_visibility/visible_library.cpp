#include "visible_library.hpp"

#include <cstdint>

namespace my_lib_visibility 
{
    uint64_t computeNchooseK(uint64_t n, uint64_t k) 
    {
        return factorial(n)/(factorial(n-k)*factorial(k));
    }

    uint64_t factorial(uint64_t n)
    {
        if(n == 1) {
            return 1;
        }
        return n * factorial(n-1);
    }

    const uint64_t random_number = 4;
}
