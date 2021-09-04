#include "snake.h"
#include <cmath>
#include <iostream>
//me
#include "SDL.h"

void Snake::Update(std::vector<SDL_Point> maze) {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdatePosition(maze);
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)
      };  // Capture the head's cell after updating.
  }

//e é aqui que podemos passar como um shared pointer a localização do maze
void Snake::UpdatePosition(std::vector<SDL_Point> maze_wall) {
  static bool cant_move;
  switch (direction) {
    case Direction::kUp:
    //std::cout << head_x << " " << head_y << " \n";
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
     /*head_y -= speed;
      speed = 0; */
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

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}


