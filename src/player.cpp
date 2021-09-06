#include "player.h"
#include <cmath>
#include <iostream>
#include "SDL.h"

//update position taking the maze in consideration
void Player::UpdatePosition(std::vector<SDL_Point> maze_wall) {
  static bool cant_move;
  switch (direction) {
    case Direction::kUp:
      cant_move = false;
      for (auto i: maze_wall){
        if (((head_y-1)==i.y) && (head_x==i.x)){
          cant_move = true; 
        }
      }
    if (!cant_move) {
      head_y -= speed;
      speed = 0;
    }
    break;
    case Direction::kDown:
    cant_move = false;
      for (auto i: maze_wall){
        if (((head_y+1)==i.y) && (head_x==i.x)){
          cant_move = true; 
        }
      }
    if (!cant_move) {
      head_y += speed;
      speed = 0;
    }
    break;
    case Direction::kLeft:
    cant_move = false;
      for (auto i: maze_wall){
        if (((head_x-1)==i.x) && (head_y==i.y)){
          cant_move = true; 
        }
      }
    if (!cant_move) {
      head_x -= speed;
      speed = 0;
    }
    break;
    case Direction::kRight:
    cant_move = false;
      for (auto i: maze_wall){
        if (((head_x+1)==i.x) && (head_y==i.y)){
          cant_move = true; 
        }
      }
    if (!cant_move) {
      head_x += speed;
      speed = 0;
    }
    break;
  }

  // Wrap the Player around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}
