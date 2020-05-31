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

  void update(float deltaTime);

  [[nodiscard]]
  Player &getPlayer(){
    return player;
  }

  template <typename T, typename... Args>
  void addEvent(Args &&... args){
    events.push_back(std::make_unique<T>(std::forward<Args>(args)...));
  }

private:
  Player player;
  std::vector<std::unique_ptr<Event>> events;

};
}


#endif //LABO_LEVEL_H
