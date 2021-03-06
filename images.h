//
// Created by baka475 on 03.02.20.
//

#ifndef JNP1_7_PROJECT_IMAGES_H
#define JNP1_7_PROJECT_IMAGES_H

#include "coordinate.h"
#include "color.h"
#include "functional.h"
#include <functional>
#include <cassert>
#include <cmath>

using Fraction = float;

template<typename T>
using Base_image = std::function<T(const Point)>;

using Region = Base_image<bool>;

using Image = Base_image<Color>;

using Blend = Base_image<Fraction>;

namespace Detail {
    static Point rotatePoint(Point p, double phi) {
        if (!p.is_polar) {
            Point p_c = to_polar(p);
            Point p_r(p_c.first, p_c.second - phi, true);
            return from_polar(p_r);
        } else {
            return from_polar(Point(p.first, p.second - phi, true));
        }
    }

    static Point translatePoint(Point p, Vector v) {
        assert(!p.is_polar);
        return Point(p.first - v.first, p.second - v.second, false);
    }

    static Point scalePoint(Point p, double scale) {
        assert(!p.is_polar);
        return Point(p.first/scale, p.second/scale, false);
    }

    static Point checkToPolar (Point p) {
        return p.is_polar ? p : to_polar(p);
    }

    static Point checkFromPolar (Point p) {
        return !p.is_polar ? p : from_polar(p);
    }

    static Point convertPoint(Point p, double d) {
        Coordinate first = p.first;
        Coordinate second = p.second;

        return Point(
        first < 0 ? first + 2*(int)(fabs(first/d) + 2)*d : first,
        second < 0 ? second + 2*(int)(fabs(second/d) + 2)*d : second);
    }

    static Point polarCheckerPoint(Point p, int n) {
        return Point(checkToPolar(p).first, checkToPolar(p).second*((double)n/M_PI), false);
    }

}

template<typename T>
Base_image<T> constant(const T t) {
    return [t](Point p) {
        assert(p.is_polar || !p.is_polar);
        return t;
    };
}

template<typename T>
Base_image<T> rotate(Base_image<T> image, double phi) {
    Base_image<T> fun = std::function([image, phi](Point p) {
        return compose(std::bind(Detail::rotatePoint, std::placeholders::_1, phi), image)(p);
    });

    return fun;
}

template <typename T>
Base_image<T> translate(Base_image<T> image, Vector v) {
    Base_image<T> fun = std::function([image, v](Point p) {
        return compose(std::bind(Detail::translatePoint, std::placeholders::_1, v), image)(p);
    });
    return fun;
}

template <typename T>
Base_image<T> scale(Base_image<T> image, double s) {
    Base_image<T> fun = std::function([image, s](Point p) {
        return compose(std::bind(Detail::scalePoint, std::placeholders::_1, s), image)(p);
    });
    return fun;
}

template <typename T>
Base_image<T> circle(Point q, double r, T inner, T outer) {
    return [=] (Point p) {
        return distance(Detail::checkFromPolar(p), Detail::checkFromPolar(q)) > r ? outer : inner;
    };
}

template <typename T>
Base_image<T> vertical_stripe(double d, T this_way, T that_way) {
    return [=](Point p) {
        return fabs(p.first) <= d/2 ? this_way : that_way;
    };
}

template <typename T>
Base_image<T> checker(double d, T this_way, T that_way) {
    return [=](Point p) {
        Point p_c = Detail::convertPoint(p, d);
        return  (((int) (p_c.first/d) + (int) (p_c.second/d))%2 == 0 ? this_way : that_way);
    };
}

template <typename T>
Base_image<T> rings(Point q, double d, T this_way, T that_way) {
    return [=](Point p) {
        return (int)(distance(Detail::checkFromPolar(q), Detail::checkFromPolar(p))/d) % 2 == 0 ? this_way : that_way;
    };
}

template <typename T>
Base_image<T> polar_checker(double d, int n, T this_way, T that_way) {
    return [=](Point p) {
        return ((int) (Detail::checkToPolar(p).second / (M_PI*2/n)) % 2 == 0) ?
            checker(d, this_way, that_way)(Detail::polarCheckerPoint(p, 4)) :
            checker(d, that_way, this_way)(Detail::polarCheckerPoint(p, 4 ));
    };
}

Image cond(Region region, Image this_way, Image that_way);

Image lerp(Blend blend, Image this_way, Image that_way);

Image darken(Image image, Blend blend);

Image lighten(Image image, Blend blend);



#endif //JNP1_7_PROJECT_IMAGES_H
