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
  //SDL_Point test = *_location;
  //_location->x = head_x;
  //location->y = head_y;        
  //UpdateHead(maze);
  UpdatePosition(maze);
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    //UpdateBody(current_cell, prev_cell);
  }
}
//e é aqui que podemos passar como um shared pointer a localização do maze
void Snake::UpdateHead(SDL_Point maze_wall) {
  switch (direction) {
    case Direction::kUp:
      if (((head_y-1)==maze_wall.y) && (head_x==maze_wall.x)){
      head_y = head_y; //nop
      }
      else head_y -= speed;
      speed = 0;
      break;

    case Direction::kDown:
      if (((head_y+1)==maze_wall.y) && (head_x==maze_wall.x)){
        head_y = head_y; //nop
      }
      else head_y += speed;
      speed = 0;
      break;

    case Direction::kLeft:
    if (((head_x-1)==maze_wall.x) && (head_y==maze_wall.y)){
      head_x = head_x;
    }
    else head_x -= speed;
      speed = 0;
      break;

    case Direction::kRight:
    if (((head_x+1)==maze_wall.x) && (head_y==maze_wall.y)){
      head_x = head_x;
    }
    else head_x += speed;
      speed = 0;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

//e é aqui que podemos passar como um shared pointer a localização do maze
void Snake::UpdatePosition(std::vector<SDL_Point> maze_wall) {
  static bool cant_move;
  switch (direction) {
    case Direction::kUp:
      cant_move = false;
      for (auto i: maze_wall){
      //std::cout << i._location.x << " " << i._location.y << " \n"; //ok, aqui está funcionando, pelo menos o log fica...então já temos um vetor de enemies
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
        //std::cout << i._location.x << " " << i._location.y << " \n"; //ok, aqui está funcionando, pelo menos o log fica...então já temos um vetor de enemies
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
        //std::cout << i._location.x << " " << i._location.y << " \n"; //ok, aqui está funcionando, pelo menos o log fica...então já temos um vetor de enemies
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
        //std::cout << i._location.x << " " << i._location.y << " \n"; //ok, aqui está funcionando, pelo menos o log fica...então já temos um vetor de enemies
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


void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    //test - doubles the size
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
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
/*
void Enemy::PlaceEnemy() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    _enemy.emplace_back(Enemy(x,y));
    // Check that the location is not occupied by a snake item before placing
    // food.
   /* if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }/*
/*
  int x = 1;
    int y = 2;
    _enemy.emplace_back(Enemy(1,2));
    
    SDL_Point ponto {4,5};
    _enemy.emplace_back(ponto);

}*/

