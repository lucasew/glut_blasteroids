//
// Created by lucas59356 on 19/11/2019.
//

#include <math.h>
#include "point.h"

/**
 * Transforma graus em radianos
 * @param deg Ãngulo em graus
 * @return Ângulo em radianos
 */
double gb_deg2rad(double deg) {
    return deg * M_PI / 180.f;
}
