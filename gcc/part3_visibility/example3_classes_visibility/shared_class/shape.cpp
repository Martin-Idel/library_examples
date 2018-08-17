#include "shape.hpp"

#include <iostream>

namespace shape_lib
{

Shape::Shape(uint32_t num_corners)
: num_corners_(num_corners)
{}

Shape::~Shape() = default;

void Shape::draw() {
    std::cout << "This shape has " << std::to_string(num_corners_) << " corners!" << std::endl;
}

}