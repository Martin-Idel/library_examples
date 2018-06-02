#include <cstdint>
#include <iostream>

namespace shape_lib
{
class CornerNumber;

class Shape {
public:
    Shape(uint32_t corner_number);

    virtual ~Shape();

    virtual void draw() const;
private:
    CornerNumber * corner_number_;
};

}