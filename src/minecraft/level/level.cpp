#include "level.h"
#include "const.h"

using glm::vec3;

labo::minecraft::Level::Level():
  player(Player({1,1,1}))
{

}


labo::minecraft::Block labo::minecraft::Level::getBlock(int x, int y, int z) {
  auto bp = getChunkLocalCoordinate(x,z);
  auto chunkLocation = getChunkLocation(x,z);

  // chunk man
}

void labo::minecraft::Level::setBlock(int x, int y, int z, labo::minecraft::Block block) {

}

void labo::minecraft::Level::update(float deltaTime) {
  player.update(deltaTime);

  for(auto &event: events){
    event->handle(*this);
  }
  events.clear();

}

labo::math::VectorXZ labo::minecraft::Level::getChunkLocalCoordinate(int x, int z) {
  return {x % CHUNK_SIZE, z % CHUNK_SIZE};
}

labo::math::VectorXZ labo::minecraft::Level::getChunkLocation(int x, int z) {
  return {x / CHUNK_SIZE, z / CHUNK_SIZE};
}


