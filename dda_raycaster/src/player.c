#include "player.h"
#include "map.h"
#include <math.h>

void player_init(Player* p) {
    p->position_x = 10.0f;
    p->position_y = 10.0f;
    p->direction_x = 1.0f;
    p->direction_y = 0.0f;
    p->plane_x = 0.0f;
    p->plane_y = 0.66f;
}

void player_move_forward(Player* p, float speed) {
    // Check X axis movement independently to allow sliding along walls.
    if (!map_is_wall((int)(p->position_x + p->direction_x * speed), (int)(p->position_y))) {
        p->position_x += p->direction_x * speed;
    }

    // Check Y axis movement independently to allow sliding along walls.
    if (!map_is_wall((int)(p->position_x), (int)(p->position_y + p->direction_y * speed))) {
        p->position_y += p->direction_y * speed;
    }
}

void player_move_backward(Player* p, float speed) {
    // Check X axis backward movement independently to prevent clipping.
    if (!map_is_wall((int)(p->position_x - p->direction_x * speed), (int)p->position_y)) {
        p->position_x -= p->direction_x * speed;
    }

    // Check Y axis backward movement independently to prevent clipping.
    if (!map_is_wall((int)p->position_x, (int)(p->position_y - p->direction_y * speed))) {
        p->position_y -= p->direction_y * speed;
    }
}

void player_rotate(Player* p, float speed) {
    // Apply a standard 2D rotation matrix to the forward direction vector.
    float old_dir_x = p->direction_x;
    p->direction_x = p->direction_x * cosf(speed) - p->direction_y * sinf(speed);
    p->direction_y = old_dir_x * sinf(speed) + p->direction_y * cosf(speed);

    // Apply the same 2D rotation matrix to the camera plane vector to keep it perpendicular.
    float old_plane_x = p->plane_x;
    p->plane_x = p->plane_x * cosf(speed) - p->plane_y * sinf(speed);
    p->plane_y = old_plane_x * sinf(speed) + p->plane_y * cosf(speed);
}