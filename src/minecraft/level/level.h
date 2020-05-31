#ifndef LABO_LEVEL_H
#define LABO_LEVEL_H

#include "../../math/non_copyable.h"
#include "../player.h"
#include "../event/event.h"
#include <vector>
#include <memory>

namespace labo::minecraft{

// In Minecraft, World is called Level
class Level: public labo::math::NonCopyable {
public:
  Level();
  ~Level();

  void update(float deltaTime);

private:
  Player player;
  std::vector<std::unique_ptr<Event>> events;

};
}


#endif //LABO_LEVEL_H
