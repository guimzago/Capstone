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

  void Update(std::vector<SDL_Point> maze);
  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  int head_x;
  int head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdatePosition(std::vector<SDL_Point> maze_wall);
  
  bool growing{false};
  int grid_width;
  int grid_height;
};


//this class can simply be a vector of SDL_Points later
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
  private:
};

#endif