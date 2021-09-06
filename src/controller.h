#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
    void SetDirection (Snake &snake , Snake::Direction direction);
    void HandleInput(bool &running, std::vector<Snake> &snake) ;
};

#endif