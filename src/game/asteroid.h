//
// Created by lucas59356 on 19/11/2019.
//

#ifndef GL_BLASTEROIDS_ASTEROID_H
#define GL_BLASTEROIDS_ASTEROID_H
#include "point.h"
#include "color.h"
#include "object.h"

/**
 * Métodos para a gambiarra de interface
 */
extern Methods_t asteroid_methods;

/**
 * Definição de Asteróide
 */
typedef struct Asteroid {
    float scale;
    float rot_velocity;
    float heading;
    float speed;
    float health;
    Point_t position;
    Color_t color;
} Asteroid_t;

/**
 * Cria um novo objeto asteroide passando os dados do mesmo
 * @param position Posição do objeto
 * @param color Cor do objeto
 * @param scale Tamanho do objeto em vezes o tamanho original
 * @param rot_velocity Velocidade de rotação do objeto
 * @param heading Para onde o objeto aponta, no caso, onde ele começa apontando
 * @param speed Velocidade do objeto
 * @param health HP do objeto
 * @return O objeto construido
 */
Asteroid_t* gb_Asteroid__new(Point_t position, Color_t color, float scale, float rot_velocity, float heading, float speed, float health);

/**
 * Cria um novo objeto asteroide utilizando parâmetros aleatórios
 * @return O objeto asteroide
 */
Asteroid_t* gb_Asteroid__new_random();

/**
 * Dar dano se a distancia entre objetos for menor que
 * @param this O objeto em que essa info vai ser obtida
 * @return Quantidade mínima de pixels de distância entre outro objeto
 */
float gb_Asteroid__get_danger_radius(Asteroid_t *this);

/**
 * Verifica se o objeto aínda é valido, ex: Asteroide destruido
 * @param a Asteroide a ser checado
 * @return Foi destruído?
 */
int gb_Asteroid__is_valid(Asteroid_t *a);

/**
 * Destroi o objeto Asteroide
 * @param obj O ponteiro do objeto a ser destruido
 */
void gb_Asteroid__destroy(Asteroid_t **obj);

/**
 * Desenha o objeto na tela
 * @param this Asteroide a ser desenhado
 */
void gb_Asteroid__draw(Asteroid_t *this);

/**
 * Atualiza o estado utilizando a velocidade de seguir e rotação por n ticks
 * @param this O objeto a ser atualizado
 * @param step Quantidade de ticks a serem percorridos
 */
void gb_Asteroid__update(Asteroid_t *this);

/**
 * Transforma em um pacote seguindo a interface
 * @param obj Objeto a ser codificado
 * @return O objeto em formato de pacote
 */
Packet_t gb_Asteroid__as_packet(Asteroid_t *obj);

/**
 * Dado um pacote, este pacote encapsula um asteroide?
 * @param pkt Pacote a ser testado
 * @return É um asteróide?
 */
int gb_Packet__is_asteroid(Packet_t* pkt);

#endif //GL_BLASTEROIDS_ASTEROID_H
