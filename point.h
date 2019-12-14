//
// Created by lucas59356 on 19/11/2019.
//

#ifndef GL_BLASTEROIDS_POINT_H
#define GL_BLASTEROIDS_POINT_H

/**
 * Define como é um ponto de localização no plano cartesiano do jogo
 */
typedef struct Point {
    float x;
    float y;
} Point_t;

/**
 * Cria um objeto ponto dado x e y do mesmo
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Objeto com as coordenadas
 */
Point_t gb_Point__new(float x, float y);

/**
 * Calcula a distancia entre dois pontos
 * @param a primeiro ponto
 * @param b segundo ponto
 * @return Distância entre os pontos
 */
double gb_Point__get_distance(Point_t a, Point_t b);
/**
 * Soma dois pontos
 * @param a Ponto A
 * @param b Ponto B
 * @return Ponto resultado da soma dos dois
 */
Point_t gb_Point__sum(Point_t a, Point_t b);

/**
 * Subtrai dois pontos
 * @param a Ponto A
 * @param b Ponto B
 * @return Ponto resultado da subtração dos dois
 */
Point_t gb_Point__sub(Point_t a, Point_t b);

/**
 * Calcula o ponto mais uma distância escalar na direção de dado grau
 * @param p Ponto a ser calculado
 * @param heading Direção do vetor
 * @param distance Distância até o novo ponto
 * @return
 */
Point_t gb_Point__go_headed(Point_t p, float heading, float distance);

Point_t gb_Point__corrigir_posicao(Point_t *p);
#endif //GL_BLASTEROIDS_POINT_H
