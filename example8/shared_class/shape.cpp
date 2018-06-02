#include "shape.hpp"

namespace shape_lib
{

Shape::Shape(uint32_t corner_number)
: corner_number_(CornerNumber(corner_number)) 
{}

void Shape::draw() const
{
    std::cout << "This shape has " << corner_number_.getNumberOfCorners() << " corners!" << std::endl;
}
}