#include <cstdint>
#include <iostream>
#include <memory>

namespace shape_lib
{
class CornerNumber;

class Shape {
public:
    Shape(uint32_t corner_number);

    virtual ~Shape();

    virtual void draw() const;
private:
    std::unique_ptr<CornerNumber> corner_number_;
};

}