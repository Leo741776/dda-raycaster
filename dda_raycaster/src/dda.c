#include "player.h"
#include "map.h"
#include <math.h>

extern void draw_column(int x, int draw_start, int draw_end, int wall_type, int side);

void update_and_render(Player* p, const int w, const int h) {
    for (int x = 0; x < w; x++) {
        // Maps the screen column index to camera space range [-1, 1] 
        // where -1 represents the far-left edge and 1 represents the far-right edge.
        double camera_x = 2 * x / (double)w - 1;
        double ray_direction_x = p->direction_x + p->plane_x * camera_x;
        double ray_direction_y = p->direction_y + p->plane_y * camera_x;

        int map_x = (int)p->position_x;
        int map_y = (int)p->position_y;

        double side_distance_x;
        double side_distance_y;

        // Using an arbitrarily large literal avoids division-by-zero operations 
        // when the ray runs perfectly parallel to an axis.
        double delta_distance_x = (ray_direction_x == 0) ? 1e30 : fabs(1 / ray_direction_x);
        double delta_distance_y = (ray_direction_y == 0) ? 1e30 : fabs(1 / ray_direction_y);

        int step_x;
        int step_y;

        int hit = 0;
        int side;

        double perpendicular_wall_distance;

        if (ray_direction_x < 0) {
            step_x = -1;
            side_distance_x = (p->position_x - map_x) * delta_distance_x;
        }
        else {
            step_x = 1;
            side_distance_x = (map_x + 1.0 - p->position_x) * delta_distance_x;
        }

        if (ray_direction_y < 0) {
            step_y = -1;
            side_distance_y = (p->position_y - map_y) * delta_distance_y;
        }
        else {
            step_y = 1;
            side_distance_y = (map_y + 1.0 - p->position_y) * delta_distance_y;
        }

        while (hit == 0) {
            if (side_distance_x < side_distance_y) {
                side_distance_x += delta_distance_x;
                map_x += step_x;
                side = 0;
            }
            else {
                side_distance_y += delta_distance_y;
                map_y += step_y;
                side = 1;
            }

            if (world_map[map_x][map_y] > 0) {
                hit = 1;
            }
        }

        // Projecting Euclidean distance onto the player's view vector cancels 
        // out the radial distortion, entirely eliminating fish-eye rendering effects.
        if (side == 0) {
            perpendicular_wall_distance = (side_distance_x - delta_distance_x);
        }
        else {
            perpendicular_wall_distance = (side_distance_y - delta_distance_y);
        }

        int line_height = (int)(h / perpendicular_wall_distance);

        int draw_start = -line_height / 2 + h / 2;
        if (draw_start < 0) {
            draw_start = 0;
        }

        int draw_end = line_height / 2 + h / 2;
        if (draw_end >= h) {
            draw_end = h - 1;
        }

        draw_column(x, draw_start, draw_end, world_map[map_x][map_y], side);
    }
}