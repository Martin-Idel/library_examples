#include <cstdint>
#include <iostream>

#include "./corner_number.hpp"

namespace shape_lib
{

class __attribute__ ((visibility ("hidden"))) Shape {
public:
    __attribute__ ((visibility ("default"))) Shape(uint32_t corner_number);

    __attribute__ ((visibility ("default"))) virtual ~Shape();

    __attribute__ ((visibility ("default"))) virtual void draw() const;
private:
    CornerNumber corner_number_;
};

}