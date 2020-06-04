#include "level.h"

#include <utility>
#include "const.h"
#include "format/chunk.h"

using glm::vec3;

labo::minecraft::Level::Level()
 : chunkManager(*this)
 , player(Player({1,1,1}))
{

}


labo::minecraft::Block labo::minecraft::Level::getBlock(int x, int y, int z) {
  auto bp = getChunkLocalCoordinate(x,z);
  auto chunkLocation = getChunkLocation(x,z);

  return chunkManager
  .getChunk(chunkLocation.x, chunkLocation.z)
  .getBlockAt(bp.x, y, bp.z);
}

void labo::minecraft::Level::setBlock(int x, int y, int z, labo::minecraft::Block block) {
  if(y <= 0){
    return;
  }

  auto bp = getChunkLocalCoordinate(x,z);
  auto chunkLocation = getChunkLocation(x,z);

  chunkManager
  .getChunk(chunkLocation.x, chunkLocation.z)
  .setBlock(bp.x, y, bp.z, std::move(block));
}

void labo::minecraft::Level::update(float deltaTime) {
  player.update(deltaTime);

  for(auto &event: events){
    event->handle(*this);
  }
  events.clear();

  for(auto &chunk : chunkManager.getChunks()){
    chunk.second.update(deltaTime);
  }
}

void labo::minecraft::Level::markNeedUpdate(int blockX, int blockY, int blockZ) {
  auto addChunkToUpdateBatch = [&](const sf::Vector3i &key, SubChunk &subChunk){

  };
}

labo::math::VectorXZ labo::minecraft::Level::getChunkLocalCoordinate(int x, int z) {
  return {x % CHUNK_SIZE, z % CHUNK_SIZE};
}

labo::math::VectorXZ labo::minecraft::Level::getChunkLocation(int x, int z) {
  return {x / CHUNK_SIZE, z / CHUNK_SIZE};
}


