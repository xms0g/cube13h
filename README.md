# cube13h

cube13h is a simple 3D graphics demonstration program written in Turbo C and x86 assembly for PC DOS. It demonstrates basic graphics programming techniques to render and animate a 3D cube on the screen, in mode 13h (320x200) colors.
You can download the `EXE` file from [itch.io](https://ms0g.itch.io/cube13h).

![cube13h](IMG/cube13h.gif)

## Features

| Feature                                | Description                                 |
|----------------------------------------|---------------------------------------------|
| Triangle rasterization                 | Fills triangle faces on the cube            |
| 3D vertex transformations              | Applies rotation and movement               |
| Perspective projection                 | Simulates depth perception                  |
| Backface culling                       | Hides faces pointing away from the camera   |
| Bresenham's line algorithm             | Draws cube edges pixel by pixel             |
| Double buffering                       | Prevents flickering and tearing             |


## Prerequisites
- **Turbo C++** (`TCC.EXE`) version 3.0 or later  
- **Turbo Assembler** (`TASM.EXE`) version 4.1 or later  
- **Turbo Linker** (`TLINK.EXE`) version 5.0 or later  
- **DOSBox** emulator or a real MS-DOS-compatible computer

## Controls
- ESC to exit the application.
- UP/DOWN to zoom in/zoom out.
- RIGHT/LEFT to move horizontally.

## Building from Source
If you want to build `cube13h` from source, you'll need Turbo C++ and the related [build tools](https://github.com/ms0g/breakout/tree/main/TOOLS/tcpp). 

## License
This project is licensed under the BSD 3-Clause License. See the LICENSE file for details.
