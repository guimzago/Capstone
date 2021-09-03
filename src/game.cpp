#include "game.h"
#include <iostream>
#include "SDL.h"
//me
#include <thread>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      snake2(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
        snakes.emplace_back(Snake(grid_width,grid_height));
        snakes.emplace_back(grid_width/2,grid_height/2);
        std::cout << snake.head_x << " " << snake.head_y << " \n";
        std::cout << snakes[0].head_x << " " << snakes[0].head_y << " \n";
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
    
    renderer.Render(snake, snake2, food, _wall, _enemy, snakes);
    //std::thread tRenderer = std::thread(&Renderer::Render, renderer, snake, food);
    //tRenderer.join();
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, snake.head_x, snake.head_y); //test
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

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  /*snake.Update(_wall); //chama snake update aqui, mas
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
*/

  snakes[0].Update(_wall); //chama snake update aqui, mas
  int new_x = static_cast<int>(snakes[0].head_x);
  int new_y = static_cast<int>(snakes[0].head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    snake.GrowBody();
    PlaceEnemy();
    PlaceWall();
    //test to print vector every enemy
    for (auto i: _enemy){
      std::cout << i._location.x << " " << i._location.y << " \n"; //ok, aqui está funcionando, pelo menos o log fica...então já temos um vetor de enemies
    }
  }

  //verifies if its in the same place as an enemy
  for (auto i: _enemy){
      //std::cout << i._location.x << " " << i._location.y << " \n"; //ok, aqui está funcionando, pelo menos o log fica...então já temos um vetor de enemies
      if ((i._location.x == new_x) && (i._location.y == new_y)){
        snake.alive = false;
      }
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

float Game::GetHeadX() const { return snake.head_x;}
float Game::GetHeadY() const { return snake.head_y;}

void Game::PlaceEnemy() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    if (!snake.SnakeCell(x, y)) {
      _enemy.emplace_back(Enemy(x,y));
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

    if (!snake.SnakeCell(x, y)) {
      _wall.emplace_back(wall_point);
      return;
    }
  }
}