#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

//controller input
void Controller::HandleInput(bool &running, std::vector<Snake> &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        //player 0 controls
        case SDLK_UP:
          snake[0].speed = 1;
          snake[0].direction = Snake::Direction::kUp;
        break;
        case SDLK_DOWN:
          snake[0].speed = 1;
          snake[0].direction = Snake::Direction::kDown;
        break;
        case SDLK_LEFT:
          snake[0].speed = 1;
          snake[0].direction = Snake::Direction::kLeft;
        break;
        case SDLK_RIGHT:
          snake[0].speed = 1;
          snake[0].direction = Snake::Direction::kRight;
        break;
          //player 1 controls
        case SDLK_w:
          snake[1].speed = 1; 
          snake[1].direction = Snake::Direction::kUp;
        break;
        case SDLK_s:
          snake[1].speed = 1;
          snake[1].direction = Snake::Direction::kDown;
        break;
        case SDLK_a:
          snake[1].speed = 1;
          snake[1].direction = Snake::Direction::kLeft;
        break;
        case SDLK_d:
          snake[1].speed = 1;
          snake[1].direction = Snake::Direction::kRight;
        break;    
      }
    }
  }
}