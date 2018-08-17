#include <cstdint>

namespace shape_lib
{

class __attribute__ ((visibility ("default"))) Shape {
public:
    Shape(uint32_t num_corners);
    virtual ~Shape();

    virtual void draw();

private:
    uint32_t num_corners_;
};

}
