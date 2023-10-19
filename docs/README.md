# R8GE Documentation

Engines is a collection of modules that are used to create a game.

## Modules
- [r8ge-core](core/README.md)
  - Core module is the base of the engine.
  - Its used for basic layer management, event handling, logging, etc.
  - Used for creating a game skeleton.
  - Doesn't depend on any other module. Thus it can be used as a base for other projects. So you may use is with other libraries.
    - For example, you can use it with [SDL2](https://www.libsdl.org/), [SFML](https://www.sfml-dev.org/), [Raylib](https://www.raylib.com/), etc.
    - You can also use it with other libraries that are not related to game development, [IMGUI](https://github.com/ocornut/imgui), etc.

- [r8ge-video](video/README.md)
  - Video module is used for rendering, window creation.
  - It uses OpenGL(GLEW) for rendering.
  - It uses X11 for window creation.
