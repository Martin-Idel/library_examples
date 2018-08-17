#include <cstdint>

namespace shape_lib
{
class CornerNumber
{
public:
    CornerNumber(uint32_t number);
    ~CornerNumber();

    uint32_t getNumberOfCorners() const;

private:
    uint32_t corner_number_;
};
}