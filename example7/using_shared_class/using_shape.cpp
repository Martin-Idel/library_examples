#include "../shared_class/shape.hpp"

int main() {
    shape_lib::Shape shape = shape_lib::Shape(5);

    shape.draw();

    return 0;
}