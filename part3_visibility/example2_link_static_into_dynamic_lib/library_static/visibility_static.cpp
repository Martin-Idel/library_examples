#include "visibility_static.hpp"

#include <cstdint>

namespace my_lib_visibility 
{
    uint64_t factorial(uint64_t n)
    {
        if(n == 1) {
            return 1;
        }
        return n * factorial(n-1);
    }
}
