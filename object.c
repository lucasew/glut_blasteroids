//
// Created by lucas59356 on 19/11/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "object.h"

float gb_Object__get_danger_radius(Packet_t *p) {
    p->fn->get_danger_radius(p->payload);
}

int gb_Object__is_valid(Packet_t *p) {
    if (p == NULL) {
        return 0;
    }
    p->fn->is_valid(p->payload);
}

void gb_Object__destroy(Packet_t *p) {
    p->fn->destroy(&p->payload);
}

void gb_Object__draw(Packet_t *p) {
    p->fn->draw(p->payload);
}

void gb_Object__update(Packet_t *p) {
    p->fn->update(p->payload);
}

Point_t gb_Object__get_point(Packet_t *p) {
    return p->fn->get_point(p->payload);
}

float gb_Object__get_damage(Packet_t *p) {
    return p->fn->get_damage(p->payload);
}

void gb_Object__hurt(Packet_t *p, float amount) {
    printf("Enviando %.1f de dano a %s\n", amount, p->fn->type);
    return p->fn->hurt(p->payload, amount);
}