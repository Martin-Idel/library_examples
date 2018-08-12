#include <cstdint>

namespace shape_lib
{
class __attribute__ ((visibility ("hidden"))) CornerNumber
{
public:
    CornerNumber(uint32_t number);
    ~CornerNumber();

    uint32_t getNumberOfCorners() const;

private:
    uint32_t corner_number_;
};
}