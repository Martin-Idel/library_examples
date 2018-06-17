#include "element.hpp"

namespace node_ns
{
class ElementImpl : public Element 
{
public:
    virtual ~ElementImpl();

    void draw() override;
};
}
