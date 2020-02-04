#include <iostream>
#include <vector>
#include <algorithm>
#include "functional.h"
#include "images.h"
#include "coordinate.h"
#include "bmp.h"
#include "color.h"

int f(int a) {
    return a*2;
}

int g(int b) {
    return b + 2;
}

int h(int c) {
    return c - 3;
}

int main() {

    const Image vs = vertical_stripe(100, Colors::Caribbean_blue, Colors::blue);

    Base_image<Color> img = constant(Colors::Caribbean_blue);
    Base_image<Color> img2 = rings(Point(0, 0, true), 15 , Colors::Caribbean_blue, Colors::blue);


    create_BMP("vertical_stripe.bmp",
               400,
               300,
               img2);

}