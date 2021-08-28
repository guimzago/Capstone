#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  float GetHeadX() const;
  float GetHeadY() const;

  std::vector<Enemy> _enemy;

 private:
  Snake snake;
  SDL_Point food;
  //testing class enemy
  

  //test
  SDL_Point obstacle;
  void PlaceObstacle();
  SDL_Point maze_wall;
  void PlaceMaze();

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
  void PlaceEnemy();
};

#endif