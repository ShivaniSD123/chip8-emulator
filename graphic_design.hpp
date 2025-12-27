#pragma once
#include </opt/homebrew/include/SDL2/SDL.h>

#include <vector>

class Display {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  int scale;

 public:
  Display() : scale(10) {
    // Initializing SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Creating the window for 32 X 64 screen
    window = SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              64 * 10,  // width (scaled)
                              32 * 10,  // height (scaled)
                              SDL_WINDOW_SHOWN);

    // Creating the renderer for rendering graphics on screen
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  }

  void draw_screen(std::vector<std::vector<int> >& video_buffer) {
    // Clear screen (black)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw pixels (white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    const int SCALE = 10;

    for (int y = 0; y < 32; y++) {
      for (int x = 0; x < 64; x++) {
        if (video_buffer[y][x]) {
          SDL_Rect pixel = {x * SCALE, y * SCALE, SCALE, SCALE};
          SDL_RenderFillRect(renderer, &pixel);
        }
      }
    }

    // Show frame
    SDL_RenderPresent(renderer);
  }

  void add_delay() { SDL_Delay(16); }

  ~Display() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
};
