//
// Created by lucas59356 on 19/11/2019.
//

#include <GL/gl.h>
#include "color.h"

Color_t gb_Color__new(GLshort r, GLshort g, GLshort b) {
    struct Color ret = {
            .r = r,
            .g = g,
            .b = b
    };
    return ret;
}

Color_t gb_Color__new_black() {
    struct Color ret = {
            .r = 0,
            .g = 0,
            .b = 0
    };
    return ret;
}

Color_t gb_Color__new_white() {
    struct Color ret = {
            .r = 0,
            .g = 0,
            .b = 0
    };
    return ret;
}
