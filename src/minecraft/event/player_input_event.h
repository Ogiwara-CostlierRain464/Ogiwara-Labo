#ifndef LABO_PLAYER_INPUT_EVENT_H
#define LABO_PLAYER_INPUT_EVENT_H

#include "event.h"
#include "../level/level.h"

namespace labo::minecraft{

class PlayerInputEvent: public Event{
public:
  void handle(Level &level) override {
    // Handle input form player, like WASD, digging
  }
};

}

#endif //LABO_PLAYER_INPUT_EVENT_H
