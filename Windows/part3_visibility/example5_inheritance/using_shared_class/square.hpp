#include <cstdint>

#include "../shared_class/shape.hpp"

namespace shape_lib
{

class Square : public Shape
{
public:
    Square(uint32_t num_corners);
    ~Square() override;

    void draw() const override;
};

}
