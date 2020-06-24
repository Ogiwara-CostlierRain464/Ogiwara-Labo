#ifndef LABO_CHUNK_H
#define LABO_CHUNK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../../block/block.h"
#include "sub_chunk.h"
#include "../../../math/array_2d.h"


namespace labo::minecraft {

class Level;
class TerrainGenerator;
class Entity;

class Chunk {
public:
  Chunk() = default;
  Chunk(Level *level, const sf::Vector2i &location);

  void update(float deltaTime);

  void setBlock(int x, int y, int z, Block block);
  Block getBlockAt(int x, int y, int z);
  int getHeightAt(int x, int z);

  [[nodiscard]]
  bool hasLoaded() const noexcept;
  void load(TerrainGenerator &generator);

  SubChunk &getSubChunk(int index);

  [[nodiscard]]
  const sf::Vector2i &getLocation()const{
    return location;
  }

  std::vector<SubChunk> &getSubChunks(){
    return subChunks;
  }

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
