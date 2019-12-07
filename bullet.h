//
// Created by lucas59356 on 19/11/2019.
//

#ifndef GL_BLASTEROIDS_BULLET_H
#define GL_BLASTEROIDS_BULLET_H
#include "color.h"
#include "point.h"
#include "object.h"
#include "spaceship.h"

/**
 * Métodos da gambiarra de interface
 */
extern Methods_t bullet_methods;

/**
 * Definição de um tiro enviado pela nave
 */
typedef struct Bullet {
    float speed;
    float heading;
    int power;
    Point_t position;
    Color_t color;
} Bullet_t;

/**
 * Cria uma nova bala
 * @param position Posição inicial
 * @param color Cor
 * @param speed Velocidade
 * @param heading Para onde está indo
 * @param power Quantidade de dano que pode dar
 * @return O objeto construido
 */
Bullet_t* gb_Bullet__new(Point_t position, Color_t color, float speed, float heading, int power);

Bullet_t* gb_Bullet__from_ship(Spaceship_t* ship);

/**
 * Obtém o raio de perigo, se o objeto estiver dentro do raio houverá uma colisão
 * @param this O objeto bala a ser obtido o valor
 * @return O raio de perigo
 */
float gb_Bullet__get_danger_radius(Bullet_t *this);

/**
 * O objeto aínda é válido?
 * @param b O objeto a ser checado
 * @return É válido?
 */
int gb_Bullet__is_valid(Bullet_t *b);

/**
 * Destroi o objeto
 * @param obj Objeto a ser destruído
 */
void gb_Bullet__destroy(Bullet_t **obj);

/**
 * Desenha o objeto
 * @param this Objeto a ser desenhado
 */
void gb_Bullet__draw(Bullet_t *this);

/**
 * Atualiza o estado do objeto em n ticks utilizando a velocidade do mesmo, por exemplo
 * @param this O objeto a ter o estado atualizado
 * @param step Quantos ticks avançar
 */
void gb_Bullet__update(Bullet_t *this, float step);

/**
 * Transforma o objeto em um pacote, para a gambiarra da interface
 * @param obj O objeto em formato de pacote
 * @return
 */
Packet_t gb_Bullet__as_packet(Bullet_t *obj);


#endif //GL_BLASTEROIDS_BULLET_H
