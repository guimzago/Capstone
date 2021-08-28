#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include <memory>
#include <random>

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  //void Update();
  void Update(SDL_Point maze);

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  int head_x;
  int head_y;
  std::vector<SDL_Point> body;
  //std::shared_ptr<SDL_Point> _location; 

 private:
  //void UpdateHead();
  void UpdateHead(SDL_Point maze_wall);
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

class Enemy {
  public:
  //constructor
  Enemy(int location_x, int location_y) {
    _location.x = location_x;
    _location.y = location_y;
  };
  Enemy(SDL_Point location) {
    _location = location;
  } //another constructor
  SDL_Point _location;
  SDL_Point GetLocation() {return _location;};
/*
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
*/
  //poderia usar um vector de SDL_Points para a location

  private:
  
};

#endif