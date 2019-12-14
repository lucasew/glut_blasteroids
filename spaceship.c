//
// Created by lucas59356 on 19/11/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "color.h"
#include "point.h"
#include "object.h"

#include "spaceship.h"

const float spaceship_heading_step = 10;
const float spaceship_speed = 10;

Spaceship_t* gb_Spaceship__new(Point_t position, Color_t color, float heading, float health) {
    struct Spaceship *ret = calloc(1, sizeof(struct Spaceship));
    ret->position = position;
    ret->color = color;
    ret->heading = heading;
    ret->health = health;
    return ret;
}

Spaceship_t* gb_Spaceship__new_random() {
    Point_t p = gb_Point__new(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT);
    Color_t c = gb_Color__new(rand()%255, rand()%255, rand()%255);
    return gb_Spaceship__new(p, c, 0, 100);
}

void gb_Spaceship__destroy(Spaceship_t **ship) {
    if (ship == NULL)
        return;
    free(*ship);
    *ship = NULL;
    printf("Spaceship dead\n");
    exit(0);
}

int gb_Spaceship__is_valid(Spaceship_t *ship) {
    return ship->health > 0;
}

#define draw_line(xa, ya, xb, yb) \
    glBegin(GL_LINES); \
        glVertex2f(xa, ya); \
        glVertex2f(xb, yb); \
    glEnd();

void gb_Spaceship__draw(Spaceship_t *ship) {
    glPushMatrix();
        glTranslated(ship->position.x, ship->position.y, 0);
        glRotatef(ship->heading, 0, 0, 1);
        glLineWidth(1);
        glColor3b(ship->color.r, ship->color.g, ship->color.b);
        draw_line(-8, 9, 0, -11);
        draw_line(0, -11, 8, 9);
        draw_line(-6, 4, -1, 4);
        draw_line(6, 4, 1, 4);
    glPopMatrix();
}

double gb_Spaceship__get_danger_radius(Spaceship_t *ship) {
    return 10;
}

void gb_Spaceship__cmd_up(Spaceship_t *ship) {
    ship->position = gb_Point__go_headed(ship->position, ship->heading, spaceship_speed);
}

void gb_Spaceship__cmd_down(Spaceship_t *ship) {
    ship->position = gb_Point__go_headed(ship->position, ship->heading, -spaceship_speed);
}

void gb_Spaceship__cmd_left(Spaceship_t *ship) {
    ship->heading += spaceship_heading_step;
}

void gb_Spaceship__cmd_right(Spaceship_t *ship) {
    ship->heading -= spaceship_heading_step;
}

void nop(void* ptr, float n){}

float gb_Spaceship__get_damage(Spaceship_t *ship) {
    return 1;
}

void gb_Spaceship__hurt(Spaceship_t *ship, float amount) {
    printf("Spaceship hurt: %.1f\n", amount);
    ship->health -= amount*tick_size();
}

Point_t gb_Spaceship__get_point(Spaceship_t *ship) {
    return ship->position;
}

Methods_t spaceship_methods = {
        .type = "spaceship",
        .destroy = gb_Spaceship__destroy,
        .draw = gb_Spaceship__draw,
        .get_damage = gb_Spaceship__get_damage,
        .get_danger_radius = gb_Spaceship__get_danger_radius,
        .get_point = gb_Spaceship__get_point,
        .hurt = gb_Spaceship__hurt,
        .is_valid = gb_Spaceship__is_valid,
        .update = nop,
};

Packet_t gb_Spaceship__as_packet(Spaceship_t *ship) {
    Packet_t ret = {
            .payload = ship,
            .fn = &spaceship_methods
    };
    return ret;
}

int gb_Packet__is_spaceship(Packet_t* pkt) {
    return pkt->fn->type == spaceship_methods.type;
}