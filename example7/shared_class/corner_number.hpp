#include <cstdint>

namespace shape_lib
{
class __attribute__ ((visibility ("hidden"))) CornerNumber
{
public:
    CornerNumber(uint32_t number)
    : corner_number_(number)
    {}
    ~CornerNumber() = default;

    uint32_t getNumberOfCorners() const {return corner_number_;}

private:
    uint32_t corner_number_;
};
}