#ifndef LABO_CHUNK_MANAGER_H
#define LABO_CHUNK_MANAGER_H

#include <unordered_map>

#include "level.h"

namespace labo::minecraft{

class Chunk;

class ChunkManager{
public:
  explicit ChunkManager(Level &level);

  Chunk &getChunk(int x, int z);
  std::unordered_map<labo::math::VectorXZ, Chunk> &getChunks();

  [[nodiscard]]
  bool isChunkLoadedAt(int x, int z) const;
  [[nodiscard]]
  bool isChunkExistAt(int x, int z) const;

private:
  std::unordered_map<labo::math::VectorXZ, Chunk> chunks;

  Level &level;
};

}

#endif //LABO_CHUNK_MANAGER_H
