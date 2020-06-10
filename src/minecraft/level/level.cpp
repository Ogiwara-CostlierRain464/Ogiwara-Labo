#include "level.h"

#include <utility>
#include "const.h"
#include "format/chunk.h"
#include <thread>
#include <chrono>

using glm::vec3;
using std::unique_lock;
using std::mutex;

labo::minecraft::Level::Level()
 : chunkManager(*this)
 , player(Player({1,4,1}))
{
  setSpawnPoint();

  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  chunkLoadThreads.emplace_back([&](){ loadChunks(); });
}

labo::minecraft::Level::~Level() {
  isRunning = false;
  for(auto &thread : chunkLoadThreads){
    thread.join();
  }
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

// 別Threadで実行される
void labo::minecraft::Level::loadChunks() {
  while(isRunning){
    bool isMeshMade = false;
    int cameraChunkX = (int) player.position.x / CHUNK_SIZE;
    int cameraChunkZ = (int) player.position.z / CHUNK_SIZE;

    for(int i = 0; i < 2; i++){
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      int minX = std::max(cameraChunkX - i, 0);
      int minZ = std::max(cameraChunkZ - i, 0);
      int maxX = cameraChunkX + i;
      int maxZ = cameraChunkZ + i;

      for(int x = minX; x < maxX; x++){
        for(int z = minZ; z < maxZ; z++){
          unique_lock<mutex> lock(mainMutex);
          chunkManager.loadChunk(x, z);
        }
      }
    }
  }
}

void labo::minecraft::Level::updateSubChunks() {
  for(auto &c : chunkUpdates){
    c.second->markNeedRender();
  }
  chunkUpdates.clear();
}

void labo::minecraft::Level::setSpawnPoint() {
//  int attempts = 0;
//  int chunkX = -1;
//  int chunkZ = -1;
//  int blockX = 0;
//  int blockZ = 0;
//  int blockY = 0;
//
//  auto h = chunkManager.getTerrainGenerator().getMinimumSpawnHeight();
//
//  while (blockY <= h){
//    chunkManager.unloadChunk(chunkX, chunkZ);
//    chunkX = 100;
//    chunkZ = 150;
//    blockX = 10;
//    blockZ = 10;
//
//    chunkManager.loadChunk(chunkX, chunkZ);
//    blockY = chunkManager
//      .getChunk(chunkX, chunkZ)
//      .getHeightAt(blockX, blockZ);
//    attempts++;
//  }
  for(int i = 0; i <= 0; i++){
    for(int j = 0; j <= 0; j++){
      unique_lock<mutex> lock(mainMutex);
      chunkManager.loadChunk(i, j);
    }
  }

  //player.position = {1,3,1};
}




