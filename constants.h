//
// Created by lucas59356 on 19/11/2019.
//

#ifndef GL_BLASTEROIDS_CONSTANTS_H
#define GL_BLASTEROIDS_CONSTANTS_H

/**
 * Largura da tela
 */
extern int SCREEN_WIDTH;

/**
 * Altura da tela
 */
extern int SCREEN_HEIGHT;

/**
 * Atualizações de estado por segundo
 */
const int FPS;

/**
 * Tempo de cada frame, delay usado entre cada iteração do jogo.
 */
static inline float tick_size() {
    return 1.0/FPS;
}

#endif //GL_BLASTEROIDS_CONSTANTS_H
