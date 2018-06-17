#include "function.hpp"

#include <iostream>

#include "../factory/node_factory.hpp"
#include "../graph/element_impl.hpp"

namespace node_ns
{

void doSomeNodeMangling()
{
    auto node = newElementNode();
    node->draw();

    Element * cast_node = dynamic_cast<Element *>(node);
    if(cast_node) {
        std::cout << "That is correct, I'm an element" << std::endl;
    } else {
        std::cout << "What went wrong here?" << std::endl;
    }
    delete node;
}
}