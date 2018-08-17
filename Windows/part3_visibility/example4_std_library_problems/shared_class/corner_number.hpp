#include <cstdint>

namespace shape_lib
{
class __declspec ( dllexport ) CornerNumber
{
public:
    CornerNumber(uint32_t number);
    ~CornerNumber();

    uint32_t getNumberOfCorners() const;

private:
    uint32_t corner_number_;
};
}