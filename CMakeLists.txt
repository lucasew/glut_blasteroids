project(gl_blasteroids C)

add_executable(main main.c asteroid.c constants.c bullet.c point.c math_utils.c color.c spaceship.c object.c object_list.c)

IF (WIN32)
    target_link_libraries(main glut32 opengl32 glu32 m)
ELSE()
    target_link_libraries(main glut GL GLU m)
ENDIF()
