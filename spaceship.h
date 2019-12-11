//
// Created by lucas59356 on 19/11/2019.
//

#ifndef GL_BLASTEROIDS_SPACESHIP_H
#define GL_BLASTEROIDS_SPACESHIP_H
#include "color.h"
#include "point.h"
#include "object.h"

/**
 * Quantos graus a nave vira por cada vez que o botão é apertado?
 */
extern const float spaceship_heading_step;

/**
 * Quantos pixels a nave vai deslocar a cada vez que o botão é apertado
 */
extern const float spaceship_speed;

/**
 * Define a estrutura de dados da nave
 */
typedef struct Spaceship {
    Color_t color;
    Point_t position;
    float heading;
    float health;
} Spaceship_t;

/**
 * Cria o objeto nave
 * @param position Posição inicial da nave
 * @param color Cor da nave
 * @param heading Direção para onde a nave está apontada
 * @param health HP da nave
 * @return O objeto nave com os dados indicados
 */
Spaceship_t* gb_Spaceship__new(Point_t position, Color_t color, float heading, float health);

/**
 * Cria um novo objeto nave randômico
 * @return
 */
Spaceship_t* gb_Spaceship__new_random();

/**
 * Obtém o raio de perigo do objeto nave
 * @param ship Objeto nave a ser consultado
 * @return O raio de perigo
 */
double gb_Spaceship__get_danger_radius(Spaceship_t *ship);

/**
 * Verifica se o objeto aínda é válido, ex: se não foi destruído
 * @param ship Nave a ser verificada
 * @return A nave aínda é válida?
 */
int gb_Spaceship__is_valid(Spaceship_t *ship);

/**
 * Interpreta o comando de seta para baixo
 * @param ship Nave a ser controlada
 */
void gb_Spaceship__cmd_down(Spaceship_t *ship);

/**
 * Interpreta o comando de seta para a esquerda
 * @param ship Nave a ser controlada
 */
void gb_Spaceship__cmd_left(Spaceship_t *ship);

/**
 * Interpreta o comando de seta para a direita
 * @param ship Nave a ser controlada
 */
void gb_Spaceship__cmd_right(Spaceship_t *ship);

/**
 * Interpreta o comando de seta para cima
 * @param ship Nave a ser controlada
 */
void gb_Spaceship__cmd_up(Spaceship_t *ship);

/**
 * Destroi o objeto nave
 * @param ship Nave a ser destruída
 */
void gb_Spaceship__destroy(Spaceship_t **ship);

/**
 * Desenha a nave
 * @param ship O objeto nave a ser desenhado
 */
void gb_Spaceship__draw(Spaceship_t *ship);

Methods_t spaceship_methods;
/**
 * Encapsula o objeto nave em um objeto pacote, gambiarra de interface
 * @param obj Objeto nave a ser encapsulado
 * @return Objeto Packet construido do objeto nave
 */
Packet_t gb_Spaceship__as_packet(Spaceship_t *obj);

/**
 * Dado um pacote, checa se este é uma nave
 * @param pkt Pacote a ser testado
 * @return É uma nave?
 */
int gb_Packet__is_spaceship(Packet_t* pkt);

#endif //GL_BLASTEROIDS_SPACESHIP_H
