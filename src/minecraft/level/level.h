#ifndef LABO_LEVEL_H
#define LABO_LEVEL_H

#include "../../math/non_copyable.h"
#include "../event/event.h"
#include "../block/block.h"
#include "../../math/vector_xz.h"
#include "chunk_manager.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <mutex>
#include <thread>
#include "../player.h"

namespace labo::minecraft{

class SubChunk;

// In Minecraft, World is called Level
class Level: public labo::math::NonCopyable {
public:
  Level();
  ~Level();

  Block getBlock(int x, int y, int z);
  void setBlock(int x, int y, int z, const Block &block);

  void update(float deltaTime);
  /**
   * ブロックの設置などによって更新が必要になったChunkにマークをする
   */
  void markNeedUpdate(int blockX, int blockY, int blockZ);

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

  ChunkManager &getChunkManager(){
    return chunkManager;
  }

private:
  /**
   * チャンクを読み込む(別スレッドで実行される)
   */
  void loadChunks();
  void updateSubChunks();

  ChunkManager chunkManager;
  Player player;
  std::vector<std::unique_ptr<Event>> events;
  std::unordered_map<sf::Vector3i, SubChunk *> chunkUpdates;

  bool isRunning = true;
  std::mutex mainMutex;
  std::vector<std::thread> chunkLoadThreads;
};
}


#endif //LABO_LEVEL_H
