//
// Created by lucas59356 on 19/11/2019.
//

#include <stdio.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <assert.h>
#include "point.h"
#include "color.h"
#include "bullet.h"
#include "object.h"
#include "spaceship.h"


Bullet_t* gb_Bullet__new(Point_t position, Color_t color, float speed, float heading, int power) {
   Bullet_t* ret = calloc(1, sizeof(Bullet_t));
   assert(ret);
   ret->color = color;
   ret->position = position;
   ret->heading = heading;
   ret->speed = speed;
   ret->power = power;
   return ret;
}

Bullet_t* gb_Bullet__from_ship(Spaceship_t* ship) {
    Color_t color = gb_Color__new(rand()%256, rand()%256, rand()%256);
    return gb_Bullet__new(ship->position, color, (float)(rand()%20), ship->heading, rand()%100);
}

void gb_Bullet__destroy(Bullet_t **obj) {
    free(*obj);
    *obj = NULL;
}

void gb_Bullet__update(Bullet_t *this, float step) {
    this->position = gb_Point__go_headed(this->position, this->heading, this->speed);
}

double gb_Bullet__get_danger_radius(Bullet_t *this) {
    // TODO: Tunar
    return 1;
}

void gb_Bullet__draw(Bullet_t *this) {
    printf("Draw bullet");
    glPushMatrix();
        glTranslated(this->position.x, this->position.y, 0);
        glPointSize(4);
        glColor3b(this->color.r, this->color.g, this->color.b);
        glBegin(GL_POINTS);
            glVertex2d(0, 0);
        glEnd();
    glPopMatrix();
}

int gb_Bullet__is_valid(Bullet_t *b) {
    return b->power > 0;
}

Point_t gb_Bullet__get_point(Bullet_t *b) {
    return b->position;
}

int gb_Bullet__get_damage(Bullet_t *b) {
    return b->power;
}

void gb_Bullet__hurt(Bullet_t *b, int amount) {
    b->power -= amount;
}

Methods_t bullet_methods = {
        .type = "bullet",
        .destroy = gb_Bullet__destroy,
        .draw = gb_Bullet__draw,
        .get_damage = gb_Bullet__get_damage,
        .get_danger_radius = gb_Bullet__get_danger_radius,
        .get_point = gb_Bullet__get_point,
        .hurt = gb_Bullet__hurt,
        .is_valid = gb_Bullet__is_valid,
        .update = gb_Bullet__update,
};

Packet_t gb_Bullet__as_packet(Bullet_t *b) {
    Packet_t ret = {
            .fn = &bullet_methods,
            .payload = b
    };
    return ret;
}