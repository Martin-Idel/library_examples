#include <cstdint>

namespace shape_lib
{
class CornerNumber;

class Shape {
public:
    Shape(uint32_t corner_number);
    ~Shape();

    void draw() const;
private:
    CornerNumber * corner_number_;
};

}