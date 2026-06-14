#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool is_running = false;


uint32_t *color_buffer = NULL;
SDL_Texture *colour_buffer_texture = NULL;





void setup(void) {
  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

  // SDL Textures are used to display the contents of `color_buffer`
  colour_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            window_width, window_height);
}

void process_input() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE)
      is_running = false;
    break;
  }
}

void update() {
  // TODO
}

// Updates the SDL_Texture with contents of `color_buffer` and
// renders the texture.
void render_color_buffer() {
  SDL_UpdateTexture(colour_buffer_texture, NULL, color_buffer,
                    (int)(window_width * sizeof(uint32_t)));
  SDL_RenderCopy(renderer, colour_buffer_texture, NULL, NULL);
}

void set_bg(uint32_t color) {
  for (int y = 0; y < window_height; y++) {
    for (int x = 0; x < window_width; x++) {
      color_buffer[(window_width * y) + x] = color;
    }
  }
}

// Draw a background grid that fills the entire window.
// Lines should be rendered at every row/col multiple of argument `spacing`.
void draw_grid(int spacing) {
  uint32_t color_bg = 0xFF000000;
  uint32_t color_grid = 0xFFFFFFFF;

  for (int y = 0; y < window_height; y++) {
    for (int x = 0; x < window_width; x++) {
      if ((x % spacing) == 0 || (y % spacing) == 0) {
        color_buffer[(window_width * y) + x] = color_grid;
      } else {
        color_buffer[(window_width * y) + x] = color_bg;
      }
    }
  }
}

void draw_rectangle(int offset_x, int offset_y, int width, int height,
                    uint32_t color) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      color_buffer[(window_width * (y + offset_y)) + (x + offset_x)] = color;
    }
  }
}

void render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // draw_grid(100);
  draw_rectangle(200, 200, 800, 600, 0xFFFFFFFF);
  render_color_buffer();

  SDL_RenderPresent(renderer);
}

void destroy_window(void) {
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(void) {
  is_running = initialize_window();

  setup();

  while (is_running) {
    process_input();
    update();
    render();
  }

  destroy_window();

  return 0;
}
