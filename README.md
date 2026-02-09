# SadGameEngine
⚠️ Status: Archived ⚠️ This project was developed for the purpose of learning. It is not actively maintained. A rewrite is planned for the future.

A game engine for old hardware

### Features

- create windows using Win32 API ([window.c](src/window.c))
- get input using Win32 API ([window.c](src/window.c), [input.c](src/input.c))
- load files and images using `stdio.h` and `stb_image.h` ([iostream.c](src/iostream.c))
- create OpenGL context using Win32 API ([opengl.c](src/opengl.c))
- use glew to load OpenGL functions ([main.c](src/main.c))
- store and manipulate object transforms using my own linear algebra library ([math.c](src/math.c))
- rendering textured spheres with phong shading using OpenGL ([scenes.c](src/scenes.c))

## Demo

![Demo](./resources/demo.gif)


## Controls  

Hold down the right mouse button to rotate the view, while pressing `W (forward)`, `A (left)`, `S (backward)`, `D (right)`, `Q (down)` or `E (up)` to move through the scene. You can hold `LSHIFT` to move faster.

![Demo](./resources/demo-2.gif)

## How to build

### Windows

1. run `premake-visual-studio.bat`
2. open `SadGameEngine.sln` in Visual Studio
3. build for your target platform

## How to run

### Windows

1. copy the SadGameEngine.exe from bin/WINX64 to the root folder, next to the solution (.sln) file
2. execute SadGameEngine.exe


## License
[MIT License](https://github.com/Schmicki/SadGameEngine/blob/main/LICENSE)
