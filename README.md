# R8GE
- **R**etro **8**-bit **G**ame **E**ngine, a simple game engine for 2D games.
- 3D support is planned in the future.
- Project is in early development stage.
- Project is licensed under GNU GPLv3(see [LICENSE](./LICENSE) file).

## Build
- Program has to be compiled with C++23 support.
  - GCC (tested with version **13.2.1**)
  - No other compilers have been tested yet.
- For build use CMake (tested with version **3.27.7**)

### Supported platforms
- GNU/Linux (tested on **Arch Linux** with **Xorg server** and **i3wm**)
- Windows may be supported in the future.

### Dependencies
Program is aimed to be as independent as possible.
<code># pacman -S libx11 glew</code>
- X11 (libx11)
  - For window creation.
- GLEW 
  - For OpenGL function loading from drivers.

