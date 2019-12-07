//
// Created by lucas59356 on 19/11/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "object.h"
#include "main.h"

#include "object_list.h"

ObjectList_t **gb_ObjectList__new() {
    ObjectList_t ** ret = malloc(sizeof(ObjectList_t*));
    *ret = NULL;
    return ret;
}

int gb_ObjectList__push(ObjectList_t **this, Packet_t pkt) {
    if (this == NULL) {
        return 1;
    }
    gb_lock();
        ObjectList_t toadd = {
                .this = malloc(sizeof(Packet_t)),
                .next = NULL
        };
        assert(toadd.this);
        *toadd.this = pkt;
        ObjectList_t* toaddptr = malloc(sizeof(ObjectList_t));
        assert(toaddptr);
        *toaddptr = toadd;
        toaddptr->next = *this;
        *this = toaddptr;
    gb_unlock();
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
    gb_lock();
        while (dmy != NULL) {
            ret++;
            dmy = dmy->next;
        }
    gb_unlock();
    return ret;
}

void gb_ObjectList__draw_all(ObjectList_t **this) {
    if (this == NULL) {
        return;
    }
    if (*this == NULL) {
        return;
    }
    gb_lock();
    ObjectList_t *dmy = *this;
    ObjectList_t **cur = &dmy;
    while (*cur != NULL) {
        gb_Object__draw((*cur)->this);
        *cur = (*cur)->next;
    }
    gb_unlock();
}


int gb_ObjectList__check_collision(ObjectList_t **this, float ticks) {
    if (this == NULL) {
        return 0;
    }
    gb_lock();
        int collisions = 0;
        ObjectList_t *dummy = *this;
        assert(dummy != NULL);
        ObjectList_t **outer = &dummy;
        int i = 0;
        for (ObjectList_t *inner = dummy; inner != NULL; inner = inner->next) {
            int j = 0;
            for (ObjectList_t *outer = dummy; outer != NULL; outer = outer->next) {
                printf("(%i, %i)\n", i, j);
                if (inner == outer) { // Evitar que o objeto tenha colisão com si mesmo
                    continue;
                }
                double hurtDistance = gb_Object__get_danger_radius(inner->this) + gb_Object__get_danger_radius(outer->this);
                double distance = gb_Point__get_distance(
                        gb_Object__get_point(inner->this),
                        gb_Object__get_point(outer->this)
                );
                printf("Distance %.2f Hurt %.2f\n", distance, hurtDistance);
                if (distance < hurtDistance) {
                    printf("Hurt\n");
                    // Só de um lado ou teremos o dobro de hp sendo perdido
                    gb_Object__hurt(inner->this, (int)(ticks*(float)gb_Object__get_damage(outer->this)));
                    collisions++;
                }
                j++;
            }
            i++;
        }
        printf("COLISOES %i\n", collisions);
    gb_unlock();
    return collisions;
}

void gb_ObjectList__tick_all(ObjectList_t **this, float ticks) {
    if (this == NULL) {
        return;
    }
    if (*this == NULL) {
        return;
    }
    ObjectList_t *dmy = *this;
    ObjectList_t **cur = &dmy;
    while (*cur != NULL) {
        gb_Object__update(PACKETOF(cur), ticks);
        *cur = (*cur)->next;
    }
    if (gb_ObjectList__check_collision(this, ticks)) {
        gb_ObjectList__gc(this);
    }
}

int gb_ObjectList__gc(ObjectList_t **this) {
    if (this == NULL) {
        return 0;
    }
    if (*this == NULL) {
        return 0;
    }
    int cleaned = 0;
    gb_lock();
        ObjectList_t *dmy = *this;
        ObjectList_t **cur = &dmy;
        while(*cur != NULL) {
            int isvalid = gb_Object__is_valid(PACKETOF(cur));
            if (!isvalid) {
                ObjectList_t *dummy = *cur;
                if (dummy != NULL) {
                    gb_Object__destroy(dummy->this);
                }
                *cur = dummy->next;
                free(dummy->this);
                free(dummy);
                cleaned++;
                continue;
            }
            *cur = (*cur)->next;
        }
    gb_unlock();
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

