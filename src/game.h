#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "player.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int points);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);

  int game_over;

 private:
  std::vector<Player> players;
  SDL_Point food;
  std::vector<SDL_Point> _wall;
   std::vector<SDL_Point> _enemy;
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  int points_to_win;

  void PlaceFood();
  void Update();
  void PlaceEnemy();
  void PlaceWall();
  void CheckEnemy();
  bool CheckItem(std::vector<Player> player, SDL_Point item);
};

#endif