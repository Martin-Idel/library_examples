#include "node_impl.hpp"

namespace node_ns
{

NodeImpl::NodeImpl() = default;
NodeImpl::~NodeImpl() = default;

void NodeImpl::draw()
{
    std::cout << "I'm a node" << std::endl;
}

}
