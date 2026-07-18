#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

typedef struct {
    float position_x;
    float position_y;
    float direction_x;
    float direction_y;
    float plane_x;
    float plane_y;
} Player;

void player_init(Player* p);
void player_move_forward(Player* p, float speed);
void player_move_backward(Player* p, float speed);
void player_rotate(Player* p, float speed);

#endif