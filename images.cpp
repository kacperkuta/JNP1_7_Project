#include "images.h"

Image cond(Region region, Image this_way, Image that_way) {
    return [=](Point p){
        return region(p)? this_way(p) : that_way(p);
    };
}

Image lerp(Blend blend, Image this_way, Image that_way) {
    return [=](Point p) {
        return this_way(p).weighted_mean(that_way(p), blend(p));
    };
}

Image darken(Image image, Blend blend) {
    return [=](Point p) {
        return image(p).weighted_mean(constant(Colors::black)(p), blend(p));
    };
}

Image lighten(Image image, Blend blend) {
    return [=](Point p) {
        return image(p).weighted_mean(constant(Colors::white)(p), blend(p));
    };
}
