#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();
  void Render(SDL_Point const &food, std::vector<SDL_Point> const &wall, std::vector<SDL_Point> const &enemy, std::vector<Snake> const &snakes);
  void UpdateWindowTitle(std::vector<Snake> snakes, int fps);
  std::vector<std::vector<int>> color {{0xCC, 0x7A, 0xCC},{0xAA, 0xAA, 0x55}}; //vector with the players colors - to add more player simple add onde more color
 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif