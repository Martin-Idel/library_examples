#include <cstdint>

#include "./corner_number.hpp"

namespace shape_lib
{

class Shape {
public:
    Shape(uint32_t corner_number);
    virtual ~Shape();

    virtual void draw() const;
private:
    CornerNumber corner_number_;
};

}