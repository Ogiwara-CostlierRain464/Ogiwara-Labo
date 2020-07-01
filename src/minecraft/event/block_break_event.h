#ifndef LABO_BLOCK_BREAK_EVENT_H
#define LABO_BLOCK_BREAK_EVENT_H

#include "event.h"
#include "../../math/glm.h"
#include "../player.h"
#include "../level/level.h"
#include "../entity/item_entity.h"
#include <memory>

namespace labo::minecraft{


class BlockBreakEvent: public Event{
public:
  BlockBreakEvent(
    const glm::vec3 &location,
    Player *player)
  : digSpot(location)
  , player(player)
  {}

  void handle(Level &level) override{
    auto chunkLocation =
      Level::getChunkLocation(
        static_cast<int>(digSpot.x),
        static_cast<int>(digSpot.z));

    if(level.getChunkManager().isChunkLoadedAt(chunkLocation.x, chunkLocation.z)){
      dig(level);

      auto entity = std::make_shared<Entity>(
        level.getNextEntityId(),
        digSpot,
        glm::vec3(),
        glm::vec3(),
        physics::AABB{digSpot, {1,1,1}});

      level.addEntity(entity);
    }
  }

private:
  void dig(Level &level){
    int x = static_cast<int>(digSpot.x);
    int y = static_cast<int>(digSpot.y);
    int z = static_cast<int>(digSpot.z);

    auto block = level.getBlock(x, y, z);
    level.markNeedUpdate(x, y, z);
    level.setBlock(x, y, z, Air);
  }

  glm::vec3 digSpot;
  Player *player;
};

}

#endif //LABO_BLOCK_BREAK_EVENT_H
