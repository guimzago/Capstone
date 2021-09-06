#include "game.h"
#include <iostream>
#include "SDL.h"
//me
#include <thread>

//game constructor
Game::Game(std::size_t grid_width, std::size_t grid_height, int points)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      points_to_win(points) {
        //start the players - to add more players simply emplace back one more Player
        snakes.emplace_back(Snake(grid_width,grid_height,0));
        snakes.emplace_back(Snake(grid_width,grid_height,0));
  PlaceFood();
}

//game main function - contains main game loop
void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    //controller thread
    std::thread tController = std::thread(&Controller::HandleInput , controller, std::ref(running), std::ref(snakes)); //creates thread for the controller
    //thanks to this post: https://knowledge.udacity.com/questions/428737 for helping with the "std::ref"
    //game update thread
    std::thread tUpdate = std::thread(&Game::Update, this);
    renderer.Render(food, _wall, _enemy, snakes);
    // end of the main game loop

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(snakes, frame_count); //test
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
    //join threads
    tController.join();
    tUpdate.join();
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    SDL_Point temp_food {x,y};

    if (!CheckItem(snakes, temp_food)) {
      food.x = temp_food.x;
      food.y = temp_food.y;
      return;
    }
  }
}

void Game::Update() {
  if (game_over) return;

  for (int i=0; i< snakes.size() ; i++)
  {
    if (!snakes[i].alive) {
      std::cout << "Player " << i << " won! \n";
      game_over = 1;
      return;
    }
  }

  for (auto &i: snakes){
    i.UpdatePosition(_wall);
  }  
  // Check if a player has scored(is on the same place as food)
      for (auto &i : snakes) {
        if ((i.head_x == food.x) && (i.head_y == food.y)) {
          i.score++;
          if (i.score >= points_to_win) {
            i.alive = false;
            break;
          }
          PlaceFood();
          PlaceEnemy();
          PlaceWall();
      }
  }
  CheckEnemy();
}

//this function verifies if an enemy has been hit. if yes, player loses 1 point and enemy is destroyed. 
void Game::CheckEnemy() {
    int index =0;
    for (auto &i: _enemy){
      index++;
      for (auto &j: snakes) {
        if ((i.x == j.head_x) && (i.y == j.head_y)) {
          _enemy.erase(_enemy.begin()+index-1); 
          if (j.score > 0)j.score--;
        }
      }
    }
}

void Game::PlaceEnemy() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    SDL_Point enemy_point {x,y};

    if (!CheckItem(snakes, enemy_point)) {
      _enemy.emplace_back(enemy_point);
      return;
    }
  }
}

void Game::PlaceWall() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    SDL_Point wall_point = {x,y};

    if (!CheckItem(snakes, wall_point)) {
      _wall.emplace_back(wall_point);
      return;
    }
  }
}

bool Game::CheckItem(std::vector<Snake> snake, SDL_Point item){
  bool cant_insert_item = false;
  for (auto i:snake){
    if ((i.head_x == item.x) && (i.head_y == item.y)){
      cant_insert_item = true;
    }
  }
  return cant_insert_item;
}

