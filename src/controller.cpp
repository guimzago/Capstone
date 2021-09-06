#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "player.h"

void Controller::SetDirection (Player &player , Player::Direction direction) {
  if (player.lock_movement == false) {
    player.speed = 1;
    player.direction = direction;
    player.lock_movement = true;
  }
}

//controller input - to add another Player insert key inputs here
void Controller::HandleInput(bool &running, std::vector<Player> &player) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        //player 0 controls
        case SDLK_UP:
          SetDirection (player[0] , Player::Direction::kUp);
          break;
        case SDLK_DOWN:
          SetDirection (player[0] , Player::Direction::kDown);
          break;
        case SDLK_LEFT:
          SetDirection (player[0] , Player::Direction::kLeft);
          break;
        case SDLK_RIGHT:
          SetDirection (player[0] , Player::Direction::kRight);
          break;
          //player 1 controls
        case SDLK_w:
          SetDirection (player[1] , Player::Direction::kUp);
          break;
        case SDLK_s:
          SetDirection (player[1] , Player::Direction::kDown);
          break;
        case SDLK_a:
          SetDirection (player[1] , Player::Direction::kLeft);
          break;
        case SDLK_d:
          SetDirection (player[1] , Player::Direction::kRight);
          break;    
      }
    }else if (e.type == SDL_KEYUP) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
        case SDLK_DOWN:
        case SDLK_LEFT:  
        case SDLK_RIGHT:
          player[0].lock_movement = false;
        break;
        case SDLK_w:
        case SDLK_s:
        case SDLK_a:
        case SDLK_d:
          player[1].lock_movement = false;
        break;
 
      }

    }
  }
}