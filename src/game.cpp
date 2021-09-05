#include "game.h"
#include <iostream>
#include "SDL.h"
//me
#include <thread>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
        snakes.emplace_back(Snake(grid_width,grid_height,0));
        snakes.emplace_back(Snake(grid_width,grid_height,0));
  PlaceFood();
}

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
    std::thread tController = std::thread(&Controller::HandleInput , controller, std::ref(running), std::ref(snakes)); //creates thread for the controller
    //thanks to this post: https://knowledge.udacity.com/questions/428737 for helping with the "std::ref"
    //controller.HandleInput(running, snake);
    
    //Update();
    std::thread tUpdate = std::thread(&Game::Update, this);
    
    renderer.Render(food, _wall, _enemy, snakes);
    //std::thread tRenderer = std::thread(&Renderer::Render, renderer, snake, food);
    //tRenderer.join();
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
    tController.join();
    tUpdate.join();
  }
}
/*
void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing food.
    if (!snakes[0].SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}
*/
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
  if (!snakes[0].alive) return;
  if (!snakes[1].alive) return;

  for (auto &i: snakes){
    i.Update(_wall);
  }  
  // Check if a player has scored(is on the same place as food)
      for (auto &i : snakes) {
        if ((i.head_x == food.x) && (i.head_y == food.y)) {
          i.score++;
          std::cout << " score "<< i.score << " \n"; //prints score to check
          PlaceFood();
          //snakes[0].GrowBody();
          PlaceEnemy();
          PlaceWall();
          std::cout << " score 0: " << snakes[0].score << "               score 1: " << snakes[1].score << "/n"; 
      }
  }
    int index =0;
    for (auto i: _enemy){
      index++;
      //std::cout << i._location.x << " " << i._location.y << " \n"; //ok, aqui está funcionando, pelo menos o log fica...então já temos um vetor de enemies
      if ((i._location.x == snakes[0].head_x) && (i._location.y == snakes[0].head_y)){
        //snakes[0].alive = false;
        _enemy.erase(_enemy.begin()+index-1); //this works! 
        snakes[0].score--;
        std::cout << " score 0: " << snakes[0].score << "/n";

      }
      if ((i._location.x == snakes[1].head_x) && (i._location.y == snakes[1].head_y)){
        snakes[1].alive = false;
      }
    }
}

//int Game::GetScore() const { return score; }
int Game::GetSize() const { return snakes[0].size; }

float Game::GetHeadX() const { return snakes[0].head_x;}
float Game::GetHeadY() const { return snakes[0].head_y;}

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
  bool cant_instert_item = false;
  for (auto i:snake){
    if ((i.head_x == item.x) && (i.head_y == item.y)){
      cant_instert_item = true;
    }
  }
  return cant_instert_item;
}
