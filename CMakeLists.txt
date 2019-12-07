project(gl_blasteroids C)

add_executable(main main.c asteroid.c constants.c bullet.c point.c math_utils.c color.c color.h spaceship.c spaceship.h asteroid.h bullet.h object.c object.h object_list.c object_list.h)

target_link_libraries(main glut GL GLU m)