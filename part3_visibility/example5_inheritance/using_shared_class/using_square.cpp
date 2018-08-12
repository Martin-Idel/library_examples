#include "./square.hpp"

int main() {
    auto const shape = shape_lib::Shape(5);

    shape.draw();

    return 0;
}