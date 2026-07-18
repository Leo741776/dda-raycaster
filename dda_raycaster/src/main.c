#include <SDL3/SDL.h>
#include "player.h"
#include "dda.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

static SDL_Renderer* global_renderer = NULL;

void draw_column(int x, int draw_start, int draw_end, int wall_type, int side) {
    int r = 0;
    int g = 0;
    int b = 0;

    switch (wall_type) {
    case 1:  r = 255; break;
    case 2:  g = 255; break;
    case 3:  b = 255; break;
    case 4:  r = 255; g = 255; b = 255; break;
    default: r = 255; g = 255; break;
    }

    // Halving the color intensity creates a distinct depth contrast between north/south and east/west facing walls.
    if (side == 1) {
        r /= 2;
        g /= 2;
        b /= 2;
    }

    SDL_SetRenderDrawColor(global_renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderLine(global_renderer, (float)x, (float)draw_start, (float)x, (float)draw_end);
}

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return 1;
    }

    SDL_Window* window = NULL;
    if (!SDL_CreateWindowAndRenderer("DDA Raycaster", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &global_renderer)) {
        SDL_Quit();
        return 1;
    }

    Player player;
    player_init(&player);

    float current_time = SDL_GetTicks();
    float previous_time = 0;
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        int num_keys;
        const bool* keys = SDL_GetKeyboardState(&num_keys);

        // Converting milliseconds to seconds ensures velocity variables scale correctly with standard units of time.
        previous_time = current_time;
        current_time = SDL_GetTicks();
        float frame_time = (current_time - previous_time) / 1000.0f;

        // Factoring frame delta into movement intervals guarantees uniform locomotion rates across fluctuating framerates.
        float move_speed = frame_time * 5.0f;
        float rotate_speed = frame_time * 3.0f;

        if (keys[SDL_SCANCODE_W]) {
            player_move_forward(&player, move_speed);
        }
        if (keys[SDL_SCANCODE_S]) {
            player_move_backward(&player, move_speed);
        }
        if (keys[SDL_SCANCODE_A]) {
            player_rotate(&player, -rotate_speed);
        }
        if (keys[SDL_SCANCODE_D]) {
            player_rotate(&player, rotate_speed);
        }

        SDL_SetRenderDrawColor(global_renderer, 40, 40, 40, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(global_renderer);

        update_and_render(&player, SCREEN_WIDTH, SCREEN_HEIGHT);

        SDL_RenderPresent(global_renderer);
    }

    SDL_DestroyRenderer(global_renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}