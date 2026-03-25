//
// Created by lucas59356 on 19/11/2019.
//

#ifndef GL_BLASTEROIDS_SPACESHIP_H
#define GL_BLASTEROIDS_SPACESHIP_H
#include "color.h"
#include "point.h"
#include "object.h"

/**
 * Fixed angle (in degrees) by which the spaceship rotates per user turn input.
 */
extern const float spaceship_heading_step;

/**
 * Discrete positional delta applied per movement frame when navigating.
 */
extern const float spaceship_speed;

/**
 * Core entity state for the player.
 * Implements the Object polymorphic interface (`spaceship_methods`) allowing it to be
 * managed generically. Its positional state is manually driven by explicit user input
 * rather than automatic per-tick updates.
 */
typedef struct Spaceship {
    Color_t color;
    Point_t position;
    float heading;
    float health;
} Spaceship_t;

/**
 * Allocates and initializes a new Spaceship entity.
 * Expects manual input events to drive positional updates in the core game loop.
 */
Spaceship_t* gb_Spaceship__new(Point_t position, Color_t color, float heading, float health);

/**
 * Spawns a new Spaceship at a random screen coordinate with a random RGB color,
 * 0 heading, and 100 base health.
 */
Spaceship_t* gb_Spaceship__new_random();

/**
 * Resolves the fixed collision bounds for the Spaceship.
 * Symmetrical collision logic is assumed across all entity types.
 */
double gb_Spaceship__get_danger_radius(Spaceship_t *ship);

/**
 * Verifies validity by checking if the entity retains positive health.
 * Failed checks flag the object for Garbage Collection in the object list.
 */
int gb_Spaceship__is_valid(Spaceship_t *ship);

/**
 * Applies a discrete backwards positional translation (-speed) relative to the current heading vector.
 */
void gb_Spaceship__cmd_down(Spaceship_t *ship);

/**
 * Rotates the entity heading leftwards by the discrete step angle (+degrees).
 */
void gb_Spaceship__cmd_left(Spaceship_t *ship);

/**
 * Rotates the entity heading rightwards by the discrete step angle (-degrees).
 */
void gb_Spaceship__cmd_right(Spaceship_t *ship);

/**
 * Applies a discrete forward positional translation (+speed) relative to the current heading vector.
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
