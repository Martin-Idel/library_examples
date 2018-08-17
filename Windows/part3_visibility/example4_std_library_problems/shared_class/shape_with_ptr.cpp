#include "shape_with_ptr.hpp"

#include "./corner_number.hpp"

namespace shape_lib
{

Shape::Shape(uint32_t corner_number)
: corner_number_(std::make_shared<CornerNumber>(corner_number)) 
{}

Shape::~Shape() = default;

void Shape::draw() const
{
    std::cout << "This shape has " << corner_number_->getNumberOfCorners() << " corners!" << std::endl;
}
}