#include <cstdint>

namespace my_lib_visibility 
{
    __attribute__ ((visibility ("default"))) uint64_t computeNchooseK(uint64_t n, uint64_t k);

    // static 
    uint64_t factorial(uint64_t n);
}
