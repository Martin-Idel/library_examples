#include <cstdint>

namespace my_lib_visibility 
{
    __declspec( dllexport ) uint64_t computeNchooseK(uint64_t n, uint64_t k);

    uint64_t factorial(uint64_t n);

    extern __declspec( dllexport ) const uint64_t random_number;
}
