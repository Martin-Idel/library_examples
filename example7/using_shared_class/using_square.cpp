#include "./square.hpp"

int main() {
    shape_lib::Square shape = shape_lib::Square(5);

    shape.draw();

    return 0;
}