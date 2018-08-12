#include "visible_library.hpp"
#include "../library_static/visibility_static.hpp"

#include <cstdint>

namespace my_lib_visibility 
{
    uint64_t computeNchooseK(uint64_t n, uint64_t k) 
    {
        return factorial(n)/(factorial(n-k)*factorial(k));
    }
}
