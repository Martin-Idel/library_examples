#include "corner_number.hpp"

namespace shape_lib
{
CornerNumber::CornerNumber(uint32_t number)
: corner_number_(number)
{}

CornerNumber::~CornerNumber() = default;

uint32_t CornerNumber::getNumberOfCorners() const 
{
    return corner_number_;
}

}