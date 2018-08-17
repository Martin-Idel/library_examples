#include <cstdint>
#include <iostream>

#include "./corner_number.hpp"

namespace shape_lib
{

class __declspec( dllimport ) Shape {
public:
    Shape(uint32_t corner_number);

    virtual ~Shape() = default;

    virtual void draw() const;
private:
    CornerNumber corner_number_;
};

}