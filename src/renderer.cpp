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
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
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

//test - render obstacle
void Renderer::Render(Snake const snake, SDL_Point const &food, SDL_Point const &obstacle, std::vector<SDL_Point> wall, std::vector<Enemy> enemy) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render obstacles (maze)
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
      for (auto i: enemy){
      //std::cout << i._location.x << " " << i._location.y << " \n"; //ok, aqui está funcionando, pelo menos o log fica...então já temos um vetor de enemies
        block.x = i._location.x * block.w;
        block.y = i._location.y * block.h;
        //block.x = maze.x * block.w;
        //block.y = maze.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0xFF, 0xFF);
      for (auto i: wall){
      //std::cout << i._location.x << " " << i._location.y << " \n"; //ok, aqui está funcionando, pelo menos o log fica...então já temos um vetor de enemies
        block.x = i.x * block.w;
        block.y = i.y * block.h;
        //block.x = maze.x * block.w;
        //block.y = maze.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    } 
  
  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps, float headx, float heady) {
  //test
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) + " X: " + std::to_string(headx) + " Y: " +  std::to_string(heady)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
