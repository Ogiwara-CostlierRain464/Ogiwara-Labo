#include "sub_chunk.h"
#include "../level.h"

labo::minecraft::SubChunk::SubChunk(
  const sf::Vector3i &pos,
  Level *level)
  : aabb(physics::AABB{{0,0,0},{CHUNK_SIZE,CHUNK_SIZE, CHUNK_SIZE}})
  , location(pos)
  , level(level)
{
  aabb.updatePosition({
    location.x * CHUNK_SIZE,
    location.y * CHUNK_SIZE,
    location.z * CHUNK_SIZE
  });
}



void labo::minecraft::SubChunk::setBlock(
  int x, int y, int z, Block block){

  if(isOutOfBounds(x) || isOutOfBounds(y) || isOutOfBounds(z)){
    auto globalPos = toGlobalPosition(x,y,z);
    level->setBlock(globalPos.x, globalPos.y, globalPos.z, block);
    return;
  }

  layers[y].update(block);
  blocks[getIndex(x,y,z)] = block;
}

labo::minecraft::Block labo::minecraft::SubChunk::getBlock(
  int x, int y, int z)const{

  if(isOutOfBounds(x) || isOutOfBounds(y) || isOutOfBounds(z)){
    auto globalPos = toGlobalPosition(x,y,z);
    return level->getBlock(globalPos.x, globalPos.y, globalPos.z);
  }

  return blocks[getIndex(x,y,z)];
}

void labo::minecraft::SubChunk::markNeedRender(){
  needRender = true;
}

const labo::minecraft::SubChunk::Layer
&labo::minecraft::SubChunk::getLayer(int y) const {
  if(y <= -1){
    assert(false);
    return level->getChunkManager()
    .getChunk(location.x, location.z)
    .getSubChunk(location.y - 1)
    .getLayer(CHUNK_SIZE - 1);
  } else if(y >= CHUNK_SIZE){
    assert(false);
    return level->getChunkManager()
    .getChunk(location.x, location.z)
    .getSubChunk(location.y + 1)
    .getLayer(0);
  } else{
    return layers[y];
  }
}

labo::minecraft::SubChunk &labo::minecraft::SubChunk::getAdjacentSubChunk(int dx, int dz) {
  int newX = location.x + dx;
  int newZ = location.z + dz;

  return level->getChunkManager()
    .getChunk(newX, newZ)
    .getSubChunk(location.y);
}

sf::Vector3i labo::minecraft::SubChunk::toGlobalPosition(int x, int y, int z) const{
  return {
    location.x * CHUNK_SIZE + x,
    location.y * CHUNK_SIZE + y,
    location.z * CHUNK_SIZE + z
  };
}

bool labo::minecraft::SubChunk::isOutOfBounds(int coordinate){
  return coordinate >= CHUNK_SIZE || coordinate < 0;
}

int labo::minecraft::SubChunk::getIndex(int x, int y, int z) {
  return x + z * CHUNK_SIZE + y * CHUNK_SIZE * CHUNK_SIZE;
}

