#include <cstdint>
#include <vector>

#include "../shared_class/shape.hpp"

class Shapes
{
public:
    Shapes();
    ~Shapes();

    void addShape(uint32_t corners);
    void drawAllShapes() const;

private:
    std::vector<shape_lib::Shape> shapes_;
};