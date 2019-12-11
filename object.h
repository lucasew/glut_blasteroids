//
// Created by lucas59356 on 19/11/2019.
//

#ifndef GL_BLASTEROIDS_OBJECT_H
#define GL_BLASTEROIDS_OBJECT_H

#include "point.h"
/**
 * void* é o objeto genérico
 */
#define OBJECT void*

#define PACKETOF(x) ((*x)->this)

/**
 * Representa a interface
 */
typedef struct Methods {
    const char* type;
    float (*get_danger_radius)(OBJECT);
    int (*is_valid)(OBJECT);
    void (*destroy)(OBJECT*);
    void (*draw)(OBJECT);
    void (*update)(OBJECT, float steps);
    Point_t (*get_point)(OBJECT);
    float (*get_damage)();
    void (*hurt)(OBJECT, float amount);
} Methods_t;

/**
 * Representa um pacote que é um valor que implementa a interface e encapsula
 */
typedef struct Packet {
    Methods_t *fn;
    void* payload;
} Packet_t;

/**
 * Obtem a posição do objeto
 * @param p O objeto
 * @return A posição dele
 */
Point_t gb_Object__get_point(Packet_t *p);

/**
 * Obtem o raio de perigo utilizando a artimanha da interface
 * @param p Pacote que fornece o dado
 * @return O raio de perigo
 */
float gb_Object__get_danger_radius(Packet_t *p);

/**
 * Obtem se o objeto aínda é válido
 * @param p Objeto a ser testado
 * @return É válido?
 */
int gb_Object__is_valid(Packet_t *p);

/**
 * Destroi o objeto pacote
 * @param p Pacote a ser destruído
 */
void gb_Object__destroy(Packet_t *p);

/**
 * Desenha o objeto do pacote na tela
 * @param p Objeto a ser desenhado
 */
void gb_Object__draw(Packet_t *p);

/**
 * Atualiza o estado do pacote em n ticks
 * @param p Objeto a ser atualizado
 * @param steps Quantidade de ticks
 */
void gb_Object__update(Packet_t *p, float steps);
float gb_Object__get_damage(Packet_t *p);
void gb_Object__hurt(Packet_t *p, float amount);

#endif //GL_BLASTEROIDS_OBJECT_H
