#include <iostream>
#include "node_factory.hpp"

#include "../graph/element_impl.hpp"

namespace node_ns
{

Node * newElementNode()
{
    return new ElementImpl();
}

}