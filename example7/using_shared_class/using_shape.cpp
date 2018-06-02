#include "./shapes.hpp"

int main() {
    auto shapes = Shapes();

    shapes.addShape(4);
    shapes.addShape(6);
    shapes.drawAllShapes();

    return 0;
}