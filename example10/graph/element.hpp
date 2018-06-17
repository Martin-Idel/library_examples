#include "node.hpp"

namespace node_ns
{
class Element : public Node
{
public:
    void draw() override = 0;
};
}
