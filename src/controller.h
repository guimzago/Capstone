#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"

class Controller {
 public:
    void SetDirection (Player &player , Player::Direction direction);
    void HandleInput(bool &running, std::vector<Player> &player) ;
};

#endif