#include "level.h"

#include <utility>
#include "const.h"
#include "format/chunk.h"

using glm::vec3;

labo::minecraft::Level::Level()
 : chunkManager(*this)
 , player(Player({1,1,1}))
{}


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

  updateSubChunks();
}

void labo::minecraft::Level::markNeedUpdate(int blockX, int blockY, int blockZ) {
  auto addChunkToUpdateBatch = [&](
    const sf::Vector3i &key,
    SubChunk *subChunk){
    chunkUpdates.emplace(key, subChunk);
  };

  auto chunkLocation = getChunkLocation(blockX, blockZ);
  auto subChunkIndex = blockY / CHUNK_SIZE;

  sf::Vector3i key(
    chunkLocation.x,
    subChunkIndex,
    chunkLocation.z);
  addChunkToUpdateBatch(
    key,
    &chunkManager
    .getChunk(chunkLocation.x, chunkLocation.z)
    .getSubChunk(subChunkIndex)
    );

  auto subChunkLocalCoordinate = getChunkLocalCoordinate(blockX, blockZ);
  auto inSubChunkHeight = blockY % CHUNK_SIZE;

  // もしチャンクの端(x方向)なら、更新キューに加える
  if(subChunkLocalCoordinate.x == 0){
    sf::Vector3i newKey(
      chunkLocation.x - 1,
      subChunkIndex,
      chunkLocation.z);
    addChunkToUpdateBatch(
      newKey,
      &chunkManager
      .getChunk(newKey.x, newKey.z)
      .getSubChunk(newKey.y)
      );
  }
  // もしチャンクの端(x方向側面)なら、更新キューに加える
  else if(subChunkLocalCoordinate.x == CHUNK_SIZE - 1){
    sf::Vector3i newKey(
      chunkLocation.x + 1,
      subChunkIndex,
      chunkLocation.z);
    addChunkToUpdateBatch(
      newKey,
      &chunkManager
        .getChunk(newKey.x, newKey.z)
        .getSubChunk(newKey.y)
    );
  }

  // もしチャンクの端(下面)なら、更新キューに加える
  if(inSubChunkHeight == 0){
    sf::Vector3i newKey(
      chunkLocation.x ,
      subChunkIndex - 1,
      chunkLocation.z);
    addChunkToUpdateBatch(
      newKey,
      &chunkManager
        .getChunk(newKey.x, newKey.z)
        .getSubChunk(newKey.y)
    );
  } else if(inSubChunkHeight == CHUNK_SIZE - 1){
    sf::Vector3i newKey(
      chunkLocation.x ,
      subChunkIndex + 1,
      chunkLocation.z);
    addChunkToUpdateBatch(
      newKey,
      &chunkManager
        .getChunk(newKey.x, newKey.z)
        .getSubChunk(newKey.y)
    );
  }

  // もしチャンクの端(z側面)なら、更新キューに加える
  if(subChunkLocalCoordinate.z == 0){
    sf::Vector3i newKey(
      chunkLocation.x ,
      subChunkIndex,
      chunkLocation.z - 1);
    addChunkToUpdateBatch(
      newKey,
      &chunkManager
        .getChunk(newKey.x, newKey.z)
        .getSubChunk(newKey.y)
    );
  }
    // もしチャンクの端(z側面)なら、更新キューに加える
  else if(subChunkLocalCoordinate.z == CHUNK_SIZE - 1){
    sf::Vector3i newKey(
      chunkLocation.x,
      subChunkIndex,
      chunkLocation.z + 1);
    addChunkToUpdateBatch(
      newKey,
      &chunkManager
        .getChunk(newKey.x, newKey.z)
        .getSubChunk(newKey.y)
    );
  }


}

labo::math::VectorXZ labo::minecraft::Level::getChunkLocalCoordinate(int x, int z) {
  return {x % CHUNK_SIZE, z % CHUNK_SIZE};
}

labo::math::VectorXZ labo::minecraft::Level::getChunkLocation(int x, int z) {
  return {x / CHUNK_SIZE, z / CHUNK_SIZE};
}

void labo::minecraft::Level::updateSubChunks() {
  for(auto &c : chunkUpdates){
    c.second->markNeedRender();
  }
  chunkUpdates.clear();
}


