cmake_minimum_required(VERSION 3.24)
project(sdl_raycaster C)

# Set runtime output so DLLs and Executables are born in the same directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# 1. Automatically fetch SDL3 from its official GitHub repository
include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        main # Or a specific release tag like release-3.2.0
)
FetchContent_MakeAvailable(SDL3)

# 2. Define your executable and its source files
add_executable(raycaster 
    sdl_raycaster/src/main.c
    sdl_raycaster/src/dda.c
    sdl_raycaster/src/map.c
    sdl_raycaster/src/player.c
)

# 3. Include your local header directory
target_include_directories(raycaster PRIVATE sdl_raycaster/include)

# 4. Automagically link SDL3 (Handles paths, binaries, and dependencies)
target_link_libraries(raycaster PRIVATE SDL3::SDL3)