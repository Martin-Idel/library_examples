#include "shapes.hpp"

Shapes::Shapes() = default;

Shapes::~Shapes() = default;

void Shapes::addShape(uint32_t corners)
{
    shapes_.push_back(shape_lib::Shape(corners));
}

void Shapes::drawAllShapes() const
{
    for(uint32_t i = 0; i < shapes_.size(); i++) {
        shapes_[i].draw();
    }
}