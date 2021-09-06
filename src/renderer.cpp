#include "renderer.h"
#include <iostream>
#include <string>

//me
#include "game.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Player Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(SDL_Point const &food, std::vector<SDL_Point> const &wall, std::vector<SDL_Point> const &enemy, std::vector<Player> const &players) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render enemies
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
      for (auto i: enemy){
        block.x = i.x * block.w;
        block.y = i.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

  // Render maze  
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0xFF, 0xFF);
      for (auto i: wall){
        block.x = i.x * block.w;
        block.y = i.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    } 

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
  
  //Render players
  SDL_RenderFillRect(sdl_renderer, &block);
  for (int index =0; index < players.size() ; index++) {
    block.x = players[index].head_x * block.w;
    block.y = players[index].head_y * block.h;
    SDL_SetRenderDrawColor(sdl_renderer, color[index][0], color[index][1], color[index][2], 0xFF);
    SDL_RenderFillRect(sdl_renderer, &block);
  }

 // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(std::vector<Player> players, int fps) {
  std::string title;
  for (int index =0; index < players.size() ; index++) {
    title = title + " Player " + std::to_string(index) + ":" + std::to_string(players[index].score) + "   " ;
  }
  title = title + "    FPS: " + std::to_string(fps);
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
