#include <cstdint>

namespace shape_lib
{

class __declspec( dllexport ) Shape {
public:
    /* __declspec( dllexport ) */ Shape(uint32_t num_corners);
    /* __declspec( dllexport ) */ virtual ~Shape();

    /* __declspec( dllexport ) */ virtual void draw();

private:
    uint32_t num_corners_;
};

}
