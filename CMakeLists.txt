cmake_minimum_required(VERSION 3.24)
project(sdl_raycaster C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(SDL3)

add_executable(raycaster 
    sdl_raycaster/src/main.c
    sdl_raycaster/src/dda.c
    sdl_raycaster/src/map.c
    sdl_raycaster/src/player.c
)

target_include_directories(raycaster PRIVATE sdl_raycaster/include)

target_link_libraries(raycaster PRIVATE SDL3::SDL3)