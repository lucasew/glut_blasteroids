//
// Created by lucas59356 on 19/11/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "object.h"

#include "object_list.h"
#include "bullet.h"
#include "constants.h"

ObjectList_t **gb_ObjectList__new() {
    ObjectList_t ** ret = malloc(sizeof(ObjectList_t*));
    *ret = NULL;
    return ret;
}

int gb_ObjectList__push(ObjectList_t **this, Packet_t pkt) {
    if (this == NULL) {
        return 1;
    }
    ObjectList_t toadd = {
            .this = calloc(1, sizeof(Packet_t)),
            .next = NULL
    };
    assert(toadd.this);
    *toadd.this = pkt;
    ObjectList_t* toaddptr = calloc(1, sizeof(ObjectList_t));
    assert(toaddptr);
    *toaddptr = toadd;
    toaddptr->next = *this;
    *this = toaddptr;
    return 0;
}
int gb_ObjectList__len(ObjectList_t **this) {
    if (this == NULL) {
        return 0;
    }
    if (*this == NULL) {
        return 0;
    }
    ObjectList_t *dmy = *this;
    int ret = 0;
    while (dmy != NULL) {
        ret++;
        dmy = dmy->next;
    }
    return ret;
}

void gb_ObjectList__draw_all(ObjectList_t **this) {
    if (this == NULL) {
        return;
    }
    if (*this == NULL) {
        return;
    }
    ObjectList_t *dmy = *this;
    ObjectList_t **cur = &dmy;
    while (*cur != NULL) {
        gb_Object__draw((*cur)->this);
        *cur = (*cur)->next;
    }
}


int gb_ObjectList__check_collision(ObjectList_t **this) {
    if (this == NULL) {
        return 0;
    }
    int collisions = 0;
    ObjectList_t *dummy = *this;
    assert(dummy != NULL);
    int i = 0;
    for (ObjectList_t *inner = dummy; inner != NULL; inner = inner->next) {
        int j = 0;
        for (ObjectList_t *outer = dummy; outer != NULL; outer = outer->next) {
            //printf("(%i, %i)\n", i, j);
            if (inner == outer) { // Evitar que o objeto tenha colisão com si mesmo
                goto enditer;
            }
            if (gb_Packet__is_spaceship(outer->this) && gb_Packet__is_bullet(inner->this)) {
                goto enditer;
            }
            if (gb_Packet__is_spaceship(inner->this) && gb_Packet__is_bullet(outer->this)) {
                goto enditer;
            }
            float hurtDistance = gb_Object__get_danger_radius(inner->this) + gb_Object__get_danger_radius(outer->this);
            float distance = gb_Point__get_distance(
                    gb_Object__get_point(inner->this),
                    gb_Object__get_point(outer->this)
            );
            //printf("Distance %.2f Hurt %.2f\n", distance, hurtDistance);
            if (distance < hurtDistance) {
                // Só de um lado ou teremos o dobro de hp sendo perdido
                float damage = gb_Object__get_damage(inner->this);
                printf("Hurt %s -> %s %.1f HP.\n", inner->this->fn->type, outer->this->fn->type, damage) ;
                gb_Object__hurt(outer->this, damage);
                collisions++;
            }
            enditer:
            j++;
        }
        i++;
    }
    collisions /= 2;
     printf("COLISOES %i\n", collisions);
    return collisions;
}

void gb_ObjectList__tick_all(ObjectList_t **this) {
    if (this == NULL) {
        return;
    }
    if (*this == NULL) {
        return;
    }
    ObjectList_t *dmy = *this;
    ObjectList_t **cur = &dmy;
    while (*cur != NULL) {
        gb_Object__update(PACKETOF(cur));
        *cur = (*cur)->next;
    }
    if (gb_ObjectList__check_collision(this)) {
        gb_ObjectList__gc(this);
    }
}

ObjectList_t* gb_ObjectList__gc_helper(ObjectList_t *this) {
    if (this == NULL) {
        return NULL;
    }
    if (gb_Object__is_valid(this->this) )  {
        this->next = gb_ObjectList__gc_helper(this->next);
        return this;
    } else {
        ObjectList_t* next = this->next;
        gb_Object__destroy(this->this);
        free(this->this);
        free(this);
        return next;
    }
}
int gb_ObjectList__gc(ObjectList_t **this) {
    if (this == NULL) {
        return 0;
    }
    if (*this == NULL) {
        return 0;
    }
    *this = gb_ObjectList__gc_helper(*this);
}

void gb_ObjectList__destroy_helper(ObjectList_t *this) {
    if (this->next != NULL) {
        gb_ObjectList__destroy_helper(this->next);
    }
    gb_Object__destroy(this->this);
    free(this);
}

void gb_ObjectList__destroy(ObjectList_t **this) {
    gb_ObjectList__destroy_helper(*this);
    *this = NULL;
}