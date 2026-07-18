# DDA Raycaster
This is a custom 3D raycaster engine, built from scratch in C. It features a classic fixed-grid world layout utilizing a Digital Differential Analysis (DDA) algorithm for highly efficient ray-wall intersection calculations. By projecting 2D map data into a pseudo-3D perspective, the engine implements core retro-shooter mechanics including fluid player movement, viewing angle rotations, and dynamic real-time rendering.

## How to Run
**Option 1 - Visual Studio**  
1. Ensure you have **Visual Studio 2022** installed with the **C++ CMake tools** and **vcpkg** enabled
2. Open the `sdl_raycaster_solution.sln` file
3. Set your build configuration to **x64**.
4. Press **F5** to automatically download dependencies via vcpkg, compile, and run.

**Option 2 - CMake**  
From the project root directory, open your terminal (or Developer PowerShell) and run: 
```
cmake -S . -B build  
cmake --build build --config Release
```  
Once compiled, run the executable:  

Windows: `./build/Release/raycaster.exe`  
Linux/macOS: `./build/Release/raycaster`

## Overview
**Pure C Implementation**  
Written with minimal external dependencies to maintain a clean and high performance codebase.  

**Modular Setup**  
Clearly structured separation between core engine systems:  
    - `main.c` / `main.h` - Core game loop, window initialization, and SDL3 event handling  
    - `dda.c` / `dda.h` - Grid-intersection mathematics and raycasting logic  
    - `player.c` / `player.h` - Smooth movement mechanics, collision handling, and view rotation  
    - `map.c` / `map.h` - Map grid layout, and world-data boundaries

## Screenshots
<p align="center">
  <img src="https://github.com/user-attachments/assets/09be24c8-5449-4da4-ba67-5e84a4c18860" width="50%"/>
</p>