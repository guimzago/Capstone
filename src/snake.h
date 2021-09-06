#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include <memory>
#include <random>

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, int score)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        score(score) {}
  void UpdatePosition(std::vector<SDL_Point> maze_wall);
  Direction direction = Direction::kUp;

  int speed;
  bool alive{true};
  int head_x;
  int head_y;
  int score;
 private:  
  int grid_width;
  int grid_height;
};

#endif