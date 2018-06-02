#include <iostream>

#include "../shared_class/shape.hpp"

namespace shape_lib
{

class Square : public Shape 
{
public:
    Square(uint32_t corners) : Shape(corners) {};
    ~Square() override = default;

    void draw() const override
    {
        std::cout << "This is a square" << std::endl;
        Shape::draw();
    }
};

}