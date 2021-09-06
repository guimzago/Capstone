#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::SetDirection (Snake &snake , Snake::Direction direction) {
  if (snake.lock_movement == false) {
    snake.speed = 1;
    snake.direction = direction;
    snake.lock_movement = true;
  }
}

//controller input - to add another Player insert key inputs here
void Controller::HandleInput(bool &running, std::vector<Snake> &snake) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        //player 0 controls
        case SDLK_UP:
          SetDirection (snake[0] , Snake::Direction::kUp);
          break;
        case SDLK_DOWN:
          SetDirection (snake[0] , Snake::Direction::kDown);
          break;
        case SDLK_LEFT:
          SetDirection (snake[0] , Snake::Direction::kLeft);
          break;
        case SDLK_RIGHT:
          SetDirection (snake[0] , Snake::Direction::kRight);
          break;
          //player 1 controls
        case SDLK_w:
          SetDirection (snake[1] , Snake::Direction::kUp);
          break;
        case SDLK_s:
          SetDirection (snake[1] , Snake::Direction::kDown);
          break;
        case SDLK_a:
          SetDirection (snake[1] , Snake::Direction::kLeft);
          break;
        case SDLK_d:
          SetDirection (snake[1] , Snake::Direction::kRight);
          break;    
      }
    }else if (e.type == SDL_KEYUP) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
        case SDLK_DOWN:
        case SDLK_LEFT:  
        case SDLK_RIGHT:
          snake[0].lock_movement = false;
        break;
        case SDLK_w:
        case SDLK_s:
        case SDLK_a:
        case SDLK_d:
          snake[1].lock_movement = false;
        break;
 
      }

    }
  }
}