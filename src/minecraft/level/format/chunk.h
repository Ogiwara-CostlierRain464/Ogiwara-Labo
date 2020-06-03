#ifndef LABO_CHUNK_H
#define LABO_CHUNK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../level.h"
#include "../../block/block.h"
#include "sub_chunk.h"
#include "../../../math/array_2d.h"


namespace labo::minecraft {

class Chunk {
public:
  Chunk() = default;
  Chunk(Level *level, const sf::Vector2i &location);

  void update(float deltaTime);

  void setBlock(int x, int y, int z, Block block);
  Block getBlockAt(int x, int y, int z);

  [[nodiscard]]
  bool hasLoaded() const noexcept;

private:
  void addSubChunk();

  /**
   * local座標外かどうか
   */
  [[nodiscard]]
  bool isOutOfBound(int x, int y, int z)const;

  std::vector<SubChunk> subChunks;
  math::Array2D<int, CHUNK_SIZE> highestBlocks;
  sf::Vector2i location;

  Level *level;

  bool isLoaded = false;
};
}


#endif //LABO_CHUNK_H
