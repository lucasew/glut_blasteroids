//
// Created by lucas59356 on 19/11/2019.
//

#ifndef GL_BLASTEROIDS_OBJECT_LIST_H
#define GL_BLASTEROIDS_OBJECT_LIST_H
#include "object.h"

/**
 * Definição da lista encadeada
 */
typedef struct ObjectList {
    Packet_t *this;
    struct ObjectList *next;
} ObjectList_t;

/**
 * Cria a estrutura de lista encadeada
 * @return O objeto vazio
 */
ObjectList_t **gb_ObjectList__new();

/**
 * Conta quantos elementos tem na lista
 * @param this Objeto lista
 * @return Quantidade de elementos
 */
int gb_ObjectList__len(ObjectList_t **this);

/**
 * Adiciona um elemento a estrutura
 * @param this Objeto lista
 * @param pkt Objeto a ser adicionado na lista
 * @return Retorna 0 se sucesso
 */
int gb_ObjectList__push(ObjectList_t **this, Packet_t pkt);


/**
 * Tira os objetos mortos da lista de objetos
 * @param this Lista de objetos a qual será feita a limpa
 * @return Quantidade de objetos limpos
 */
int gb_ObjectList__gc(ObjectList_t **this);


/**
 * Função ajudante recursiva que destroi todos os elementos da lista
 * @param this A lista
 */
void gb_ObjectList__destroy_helper(ObjectList_t *this);

/**
 * Destroi a lista
 * @param this A lista
 */
void gb_ObjectList__destroy(ObjectList_t **this);

/**
 * Desenha todos os objetos da lista
 * @param this A lista
 */
void gb_ObjectList__draw_all(ObjectList_t **this);

/**
 * Atualiza todos os objetos da lista em ticks estados
 * @param this A lista
 * @param ticks Quantos ticks atualizar todos os elementos
 */
void gb_ObjectList__tick_all(ObjectList_t **this, float ticks);

#endif //GL_BLASTEROIDS_OBJECT_LIST_H
