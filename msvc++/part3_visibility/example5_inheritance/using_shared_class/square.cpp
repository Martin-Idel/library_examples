#include "square.hpp"

#include <iostream>

namespace shape_lib
{

Square::Square(uint32_t num_corners)
: Shape(num_corners)
{}

Square::~Square() = default;

void Square::draw() const
{
    std::cout << "This is a square!" << std::endl;
    Shape::draw();
}
}