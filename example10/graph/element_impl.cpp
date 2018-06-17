#include "element_impl.hpp"

namespace node_ns
{

ElementImpl::~ElementImpl() = default;

void ElementImpl::draw()
{
    std::cout << "I'm an element" << std::endl;
}

}
