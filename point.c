//
// Created by lucas59356 on 19/11/2019.
//

#include <math.h>
#include "point.h"
#include "math_utils.h"
#include "constants.h"

Point_t gb_Point__new(double x, double y) {
    struct Point ret = {
            .x = x,
            .y = y
    };
    return ret;
}

Point_t gb_Point__sum(Point_t a, Point_t b) {
    struct Point ret = {
        .x = a.x + b.y,
        .y = a.y + b.y
    };
    return ret;
}

Point_t gb_Point__sub(Point_t a, Point_t b) {
    struct Point ret = {
            .x = a.x - b.y,
            .y = a.y - b.y
    };
    return ret;
}

double gb_Point__get_distance(Point_t a, Point_t b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

Point_t gb_Point__go_headed(Point_t p, double heading, double distance) {
    p.x += sin(gb_deg2rad(heading))*distance;
    p.y -= cos(gb_deg2rad(heading))*distance;
    gb_Point__corrigir_posicao(&p);
    return p;
}

Point_t gb_Point__corrigir_posicao(Point_t *p) {
    if (p->x > SCREEN_WIDTH) {
        p->x = 0;
    }
    if (p->x < 0) {
        p->x = SCREEN_WIDTH;
    }
    if (p->y > SCREEN_HEIGHT) {
        p->y = 0;
    }
    if (p->y < 0) {
        p->y = SCREEN_HEIGHT;
    }
}