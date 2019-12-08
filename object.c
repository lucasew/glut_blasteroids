//
// Created by lucas59356 on 19/11/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "object.h"

double gb_Object__get_danger_radius(Packet_t *p) {
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

void gb_Object__update(Packet_t *p, float steps) {
    p->fn->update(p->payload, steps);
}

Point_t gb_Object__get_point(Packet_t *p) {
    return p->fn->get_point(p->payload);
}

int gb_Object__get_damage(Packet_t *p) {
    return p->fn->get_damage();
}

void gb_Object__hurt(Packet_t *p, int amount) {
    printf("Enviando dano a %s\n", p->fn->type);
    return p->fn->hurt(p->payload, amount);
}