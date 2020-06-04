#ifndef LABO_SUB_CHUNK_H
#define LABO_SUB_CHUNK_H

#include "../../block/block.h"
#include "../const.h"
#include "../../../physics/aabb.h"
#include <SFML/Graphics.hpp>
#include <array>

namespace labo::minecraft{

class Level;

class SubChunk {
  friend class Chunk;

  class Layer{
  public:
    void update(const Block &block){
      if(block.isOpaque()){
        solidBlockCount--;
      }else{
        solidBlockCount++;
      }
    }

    [[nodiscard]]
    bool isAllSolid()const{
      return solidBlockCount == CHUNK_AREA;
    }

  private:
    int solidBlockCount = 0;
  };

public:
  SubChunk(const sf::Vector3i &pos, Level *level);

  void setBlock(int x, int y, int z, Block block);

  [[nodiscard]]
  Block getBlock(int x, int y, int z) const;

  [[nodiscard]]
  sf::Vector3i getLocation() const{
    return location;
  }

  [[nodiscard]]
  bool isNeedRender()const{
    return needRender;
  }

  /**
   * 再描画が必要であるとマークする
   */
  void markNeedRender();

  [[nodiscard]]
  const Layer &getLayer(int y) const;
  SubChunk &getAdjacentSubChunk(int dx, int dz);

  [[nodiscard]]
  const physics::AABB &getAABB()const{
    return aabb;
  }

  const Block *blocksFirstPtr(){
    return &blocks[0];
  }

private:
  [[nodiscard]]
  sf::Vector3i toGlobalPosition(int x, int y, int z) const;

  /**
   * SubChunkのlocal座標内か確認
   */
  static bool isOutOfBounds(int coordinate);
  /**
   * 座標の配列内のindexを算出
   */
  static int getIndex(int x, int y, int z);

  std::array<Block, CHUNK_VOLUME> blocks;
  std::array<Layer, CHUNK_SIZE> layers;

  physics::AABB aabb;
  sf::Vector3i location;

  Level *level;
  bool needRender = false;
};

}


#endif //LABO_SUB_CHUNK_H
