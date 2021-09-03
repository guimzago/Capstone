#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) {snake.direction = input;
  std::cout << "change direction" << " \n";}
  return;
}

void Controller::HandleInput(bool &running, std::vector<Snake> &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake[0], Snake::Direction::kUp,
                          Snake::Direction::kDown);
                          snake[0].speed = 1; //test speed
                          std::cout << snake[0].head_x << " " << snake[0].head_y << " \n";

          break;

        case SDLK_DOWN:
          ChangeDirection(snake[0], Snake::Direction::kDown,
                          Snake::Direction::kUp);
                          snake[0].speed = 1;
                          std::cout << snake[0].head_x << " " << snake[0].head_y << " \n";
          break;

        case SDLK_LEFT:
          ChangeDirection(snake[0], Snake::Direction::kLeft,
                          Snake::Direction::kRight);
                          snake[0].speed = 1;
                          std::cout << snake[0].head_x << " " << snake[0].head_y << " \n";
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake[0], Snake::Direction::kRight,
                          Snake::Direction::kLeft);
                          snake[0].speed = 1;
                          std::cout << snake[0].head_x << " " << snake[0].head_y << " \n";
          break;
      }
    }
  }
}