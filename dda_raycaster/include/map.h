#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

extern const int world_map[MAP_WIDTH][MAP_HEIGHT];

bool map_is_wall(int x, int y);

#endif