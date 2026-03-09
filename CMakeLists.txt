project(gl_blasteroids C)

include_directories(src src/engine src/game)

add_executable(main
    src/main.c
    src/constants.c
    src/engine/object.c
    src/engine/object_list.c
    src/engine/point.c
    src/engine/color.c
    src/engine/math_utils.c
    src/game/asteroid.c
    src/game/bullet.c
    src/game/spaceship.c
)

IF (WIN32)
    target_link_libraries(main glut32 opengl32 glu32 m)
ELSE()
    target_link_libraries(main glut GL GLU m)
ENDIF()
