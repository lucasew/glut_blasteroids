//
// Created by lucas59356 on 19/11/2019.
//

#include <stdio.h>
#include <GL/gl.h>
#include <stdlib.h>
#include "point.h"
#include "color.h"
#include "object.h"
#include "constants.h"

#include "asteroid.h"

Asteroid_t* gb_Asteroid__new(Point_t position, Color_t color, float scale, float rot_velocity, float heading, float speed, float health) {
    Asteroid_t* ret = calloc(1, sizeof(Asteroid_t));
    ret->color = color;
    ret->heading = heading;
    ret->health = health;
    ret->position = position;
    ret->rot_velocity = rot_velocity;
    ret->scale = scale;
    ret->speed = speed;
    return ret;
}

Asteroid_t* gb_Asteroid__new_random() {
    Point_t p = gb_Point__new(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT);
    Color_t c = gb_Color__new(rand()%255, rand()%255, rand()%255);
    return gb_Asteroid__new(p, c, (float)(rand()%5), rand()%100, 0, (float)(rand()%50), rand()%200);
}

void gb_Asteroid__destroy(Asteroid_t **obj) {
    free(*obj);
    *obj = NULL;
}

void gb_Asteroid__update(Asteroid_t *this) {
    this->heading += this->rot_velocity*tick_size();
    this->position = gb_Point__go_headed(this->position, this->heading, this->speed*tick_size());
}

float gb_Asteroid__get_danger_radius(Asteroid_t *this) {
    // TODO: Tunar
    return 22*this->scale;
}

/**
 * Pontos hardcodados de um asteroide, rosbado do use a cabeça C por que eu achei bonito
 */
const int asteroid_points[][2] = {
        {-20, 20},
        {-25, 5},
        {-25, -10},
        {-5, -10},
        {-10, -20},
        {5, -20},
        {20, -10},
        {20, -5},
        {0, 0},
        {20, 10},
        {10, 20},
        {0, 15}
};


void gb_Asteroid__draw(Asteroid_t *this) {
    glPushMatrix();
        glColor3b(this->color.r, this->color.g, this->color.b);
        glTranslated(this->position.x, this->position.y, 0);
        glRotatef(this->heading, 0, 0, 1);
        glScalef(this->scale, this->scale, 0) ;
        glLineWidth(1);
        glBegin(GL_POLYGON);
            for (int i = 0; i <= 12; i++) {
                glVertex2iv(asteroid_points[i%12]);
            }
        glEnd();
    glPopMatrix();
}

int gb_Asteroid__is_valid(Asteroid_t *a) {
    return a->health > 0;
}

Point_t gb_Asteroid__get_point(Asteroid_t *a) {
    return a->position;
}

float gb_Asteroid__get_damage() {
    return 1;
}

void gb_Asteroid__hurt(Asteroid_t *a, float amount) {
    a->health -= amount*tick_size();
}

Methods_t asteroid_methods = {
        .type = "asteroid",
        .destroy = gb_Asteroid__destroy,
        .draw = gb_Asteroid__draw,
        .get_damage = gb_Asteroid__get_damage,
        .get_danger_radius = gb_Asteroid__get_danger_radius,
        .get_point = gb_Asteroid__get_point,
        .hurt = gb_Asteroid__hurt,
        .is_valid = gb_Asteroid__is_valid,
        .update = gb_Asteroid__update,
};


Packet_t gb_Asteroid__as_packet(Asteroid_t *obj) {
    Packet_t ret = {
            .fn = &asteroid_methods,
            .payload = obj
    };
    return ret;
}

int gb_Packet__is_asteroid(Packet_t* pkt) {
    return pkt->fn->type == asteroid_methods.type;
}
