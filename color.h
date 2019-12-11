//
// Created by lucas59356 on 19/11/2019.
//

#ifndef GL_BLASTEROIDS_COLOR_H
#define GL_BLASTEROIDS_COLOR_H

#include <GL/gl.h>

/**
 * Definição de cor
 */
typedef struct Color {
    GLbyte r;
    GLbyte g;
    GLbyte b;
} Color_t;

/**
 * Criar um objeto cor partindo do RGB
 * @param r Cor vermelha.
 * @param g Cor verde
 * @param b Cor azul
 * @return O objeto de cor
 */
Color_t gb_Color__new(GLshort r, GLshort g, GLshort b);

/**
 * Cria um objeto com a cor preta
 * @return O objeto de cor representando a cor preta
 */
Color_t gb_Color__new_black();

/**
 * Cria um objeto com a cor branca
 * @return O objeto de cor representando a cor branca
 */
Color_t gb_Color__new_white();

#endif //GL_BLASTEROIDS_COLOR_H
