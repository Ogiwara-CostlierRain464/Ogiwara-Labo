#ifndef LABO_LEVEL_H
#define LABO_LEVEL_H

#include "../../math/non_copyable.h"
#include "../player.h"
#include "../event/event.h"
#include "../block/block.h"
#include "../../math/vector_xz.h"
#include <vector>
#include <memory>

namespace labo::minecraft{

// In Minecraft, World is called Level
class Level: public labo::math::NonCopyable {
public:
  Level();

  Block getBlock(int x, int y, int z);
  void setBlock(int x, int y, int z, Block block);

  void update(float deltaTime);

  [[nodiscard]]
  Player &getPlayer(){
    return player;
  }

  /**
   * Chunk内のlocal座標に変換
   */
  static labo::math::VectorXZ getChunkLocalCoordinate(int x, int z);
  /**
   * Chunk自体のLocationを返す
   */
  static labo::math::VectorXZ getChunkLocation(int x, int z);

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
