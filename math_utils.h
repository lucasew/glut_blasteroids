//
// Created by lucas59356 on 19/11/2019.
//

#ifndef GL_BLASTEROIDS_MATH_UTILS_H
#define GL_BLASTEROIDS_MATH_UTILS_H

/**
 * Transforma graus em radianos
 * @param deg Valor em graus
 * @return Valor em radianos
 */
double gb_deg2rad(double deg);

#define draw_line(xa, ya, xb, yb) \
    glBegin(GL_LINES); \
        glVertex2f(xa, ya); \
        glVertex2f(xb, yb); \
    glEnd();

#endif //GL_BLASTEROIDS_MATH_UTILS_H
