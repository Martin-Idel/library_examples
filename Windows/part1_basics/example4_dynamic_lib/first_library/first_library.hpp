#include <cstdint>

namespace my_lib 
{
    extern "C" __declspec( dllexport ) uint64_t addingTwoNumbers(uint64_t a, uint64_t b);
}
