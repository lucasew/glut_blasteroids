# Asteroids Project Conventions

## Codebase Map

- `main.c` -> Application entrypoint and game loop.
- `object.h` / `object.c` -> Polymorphic interface for game entities.
- `object_list.h` / `object_list.c` -> Linked list handling for game entities (rendering, ticking, GC).
- `spaceship.h` / `spaceship.c` -> Spaceship entity logic and state.
- `bullet.h` / `bullet.c` -> Bullet entity logic and state.
- `asteroid.h` / `asteroid.c` -> Asteroid entity logic and state.
- `math_utils.h` / `math_utils.c` -> Mathematical helper functions (e.g., deg2rad).
- `point.h` / `point.c` -> 2D coordinate utilities and vector math.
- `color.h` / `color.c` -> RGB color definitions.
- `constants.h` / `constants.c` -> Global game constants (SCREEN_WIDTH, SCREEN_HEIGHT, etc.).

## Documentation Guidelines

- Use Doxygen-style (`/** ... */`) comments.
- Focus on explaining the *why*, non-obvious details, and execution flow.
- Avoid redundant parameter type descriptions or "obvious" comments.
- Explain how functions fit into the larger system.
