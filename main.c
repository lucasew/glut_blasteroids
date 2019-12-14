#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "object_list.h"
#include "spaceship.h"
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "asteroid.h"
#include "bullet.h"
#include "main.h"


pthread_mutex_t lock;

ObjectList_t **elements = NULL;
Spaceship_t *spaceship = NULL;
int stop = 0;

/**
 * Função que limpa a casa quando o programa fecha, é invocada por um hook setado pela função atexit
 */
void cleanup() {
    gb_ObjectList__destroy(elements);
    pthread_mutex_destroy(&lock);
}

/**
 * Função que processa os eventos especiais de teclado
 * @param key Tecla pressionada
 * @param x Não utilizado, coisa do glut
 * @param y Não utilizado, coisa do glut
 */
void special_keyboard(int key, int x, int y) {
    gb_lock();
    switch (key) {
        case GLUT_KEY_UP:
            gb_Spaceship__cmd_up(spaceship);
            break;
        case GLUT_KEY_DOWN:
            gb_Spaceship__cmd_down(spaceship);
            break;
        case GLUT_KEY_LEFT:
            gb_Spaceship__cmd_left(spaceship);
            break;
        case GLUT_KEY_RIGHT:
            gb_Spaceship__cmd_right(spaceship);
            break;
    }
    gb_unlock();
    glutPostRedisplay(); // Se chegar aqui então redesenha
}

/**
 * Função que interpreta os eventos recebidos do teclado
 * @param key Tecla pressionada
 * @param x Não utilizado, coisa do glut
 * @param y Não utilizado, coisa do glut
 */
void keyboard(unsigned char key, int x, int y) {
    gb_lock();
    switch (key) {
        case ' ':
            gb_ObjectList__push(elements, gb_Bullet__as_packet(gb_Bullet__from_ship(spaceship)));
            break;
        case 'n':
            gb_ObjectList__push(elements, gb_Asteroid__as_packet(gb_Asteroid__new_random()));
            break;
    }
    glutPostRedisplay();
    gb_unlock();
}

/**
 * Função de desenho
 */
void draw() {
    gb_lock();
    printf("DRAW\n");
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(1, 1, 1, 0);
    gb_ObjectList__draw_all(elements); // Basicamente
    glFlush();
    glutSwapBuffers();
    printf("Quandidade de elementos: %i\n", gb_ObjectList__len(elements));
    printf("VIDA_NAVE %.1f\n", spaceship->health);
    gb_unlock();
}

/**
 * Função de atualização de estado
 * @param v Não utilizado, coisa do glut
 */
void ticker(int v) {
    if (stop) {
        return;
    }
    glutTimerFunc((unsigned int)(tick_size*1000), ticker, 0); // Fica se chamando infinitamente, bendito scheduler do glut <3
    gb_lock();
    gb_ObjectList__tick_all(elements);
    gb_unlock();
    glutPostRedisplay();
}

float asteroid_spawn_secs = 10;
void asteroid_spawner(int v) {
    while(!stop) {
        usleep(tick_size*((float)FPS)*asteroid_spawn_secs);
        gb_lock();
            gb_ObjectList__push(elements, gb_Asteroid__as_packet(gb_Asteroid__new_random()));
        gb_unlock();
        glutPostRedisplay();
    }
}

void gb_lock() {
    pthread_mutex_lock(&lock);
}

void gb_unlock() {
    pthread_mutex_unlock(&lock);
}

/**
 * Função de inicio
 * @param argc Número de parâmetros recebidos
 * @param argv Vetor de string dos parâmetros recebidos
 * @return
 */
int main(int argc, char **argv) {
    srand(time(NULL)); // Adicionando bagunça nisso
    assert(!pthread_mutex_init(&lock, NULL));
    elements = gb_ObjectList__new();
    spaceship = gb_Spaceship__new_random();
    spaceship->position.x = 200;
    spaceship->position.y = 200;
    Asteroid_t *asteroid = gb_Asteroid__new_random();
    asteroid->position.x = 200;
    asteroid->position.y = 200;
    gb_ObjectList__push(elements, gb_Spaceship__as_packet(spaceship));
    gb_ObjectList__push(elements, gb_Asteroid__as_packet(asteroid));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    atexit(cleanup);
    glutCreateWindow("GL Blasteroids");
    glutDisplayFunc(draw);
    glutSpecialFunc(special_keyboard);
    glutKeyboardFunc(keyboard);
    //asteroid_spawner(0);
    ticker(0);
    glutMainLoop();
}