//
// Created by lucas59356 on 19/11/2019.
//

#ifndef GL_BLASTEROIDS_ASTEROID_H
#define GL_BLASTEROIDS_ASTEROID_H
#include "point.h"
#include "color.h"
#include "object.h"

/**
 * Métodos para a gambiarra de interface
 */
extern Methods_t asteroid_methods;

/**
 * Definição de Asteróide
 */
typedef struct Asteroid {
    float scale;
    float rot_velocity;
    float heading;
    float speed;
    float health;
    Point_t position;
    Color_t color;
} Asteroid_t;

/**
 * Aloca dinamicamente e inicializa um novo objeto Asteróide com os dados fornecidos.
 * A memória é alocada via `calloc` e o chamador passa a ser dono do ponteiro retornado.
 *
 * @param position Posição inicial no espaço 2D
 * @param color Cor RGB para o polígono desenhado
 * @param scale Fator de escala base que afeta o tamanho e o raio de colisão do objeto
 * @param rot_velocity Velocidade angular de rotação
 * @param heading Ângulo de rotação inicial para onde o objeto aponta
 * @param speed Velocidade linear de deslocamento
 * @param health Pontos de vida do asteroide (determina se ele continua válido)
 * @return Ponteiro alocado para a nova instância de Asteroid_t, ou NULL em caso de falha
 */
Asteroid_t* gb_Asteroid__new(Point_t position, Color_t color, float scale, float rot_velocity, float heading, float speed, float health);

/**
 * Cria um objeto asteróide atuando como um obstáculo imprevisível gerando
 * parâmetros aleatórios, incluindo posição de spawn dentro dos limites da tela,
 * cor RGB, tamanho, velocidade, saúde e rotação.
 *
 * @return Um novo ponteiro alocado de Asteroid_t.
 */
Asteroid_t* gb_Asteroid__new_random();

/**
 * Calcula dinamicamente o raio da 'hitbox' do asteroide baseado no
 * seu atributo 'scale'. É usado pelo gerenciador de colisões para
 * verificar intersecção com naves, balas e outros asteroides.
 *
 * @param this O objeto do asteroide sendo testado
 * @return O valor do raio efetivo de colisão deste objeto em pixels.
 */
float gb_Asteroid__get_danger_radius(Asteroid_t *this);

/**
 * Verifica se o objeto aínda é valido, ex: Asteroide destruido
 * @param a Asteroide a ser checado
 * @return Foi destruído?
 */
int gb_Asteroid__is_valid(Asteroid_t *a);

/**
 * Libera de forma segura a memória alocada do objeto asteroide
 * e zera o seu ponteiro (anulação `*obj = NULL`) para evitar acessos
 * inválidos posteriores (dangling pointers).
 *
 * @param obj Endereço do ponteiro do asteroide a ser desalocado
 */
void gb_Asteroid__destroy(Asteroid_t **obj);

/**
 * Desenha o objeto na tela
 * @param this Asteroide a ser desenhado
 */
void gb_Asteroid__draw(Asteroid_t *this);

/**
 * Avança o estado espacial do asteroide (posição e rotação angular)
 * linearmente ao longo do tempo. Leva em consideração o tempo decorrido no
 * último frame global (`tick_size`).
 *
 * @param this O asteroide alvo da atualização
 */
void gb_Asteroid__update(Asteroid_t *this);

/**
 * Transforma em um pacote seguindo a interface
 * @param obj Objeto a ser codificado
 * @return O objeto em formato de pacote
 */
Packet_t gb_Asteroid__as_packet(Asteroid_t *obj);

/**
 * Dado um pacote, este pacote encapsula um asteroide?
 * @param pkt Pacote a ser testado
 * @return É um asteróide?
 */
int gb_Packet__is_asteroid(Packet_t* pkt);

#endif //GL_BLASTEROIDS_ASTEROID_H
