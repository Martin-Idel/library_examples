#include "node.hpp"

namespace node_ns
{
class NodeImpl : public Node
{
public:
    NodeImpl();
    virtual ~NodeImpl();

    void draw() override;
};
}
