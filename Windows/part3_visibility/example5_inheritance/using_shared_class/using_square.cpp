#include "./square.hpp"

int main() {
    auto const shape = shape_lib::Square(5);

    shape.draw();

    return 0;
}