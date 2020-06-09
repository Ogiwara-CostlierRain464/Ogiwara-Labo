#include "chunk.h"
#include "../generator/generator.h"

labo::minecraft::Chunk::Chunk(
  labo::minecraft::Level *level,
  const sf::Vector2i &location)
  : location(location)
  , level(level)
{
  highestBlocks.setAll(0);
}

void labo::minecraft::Chunk::update(float deltaTime) {
  ;
}

void labo::minecraft::Chunk::setBlock(
  int x, int y, int z,
  labo::minecraft::Block block) {
  // add sub chunk stack until y
  int index = y / CHUNK_SIZE;
  while ((int) subChunks.size() < index+1){
    addSubChunk();
  }

  if(isOutOfBound(x,y,z)){
    return;
  }

  int bY = y % CHUNK_SIZE;
  subChunks[y / CHUNK_SIZE].setBlock(x, bY, z, block);

  if(y == highestBlocks.get(x,z)){
    auto highBlock = getBlockAt(x, y--, z);
    while (!highBlock.isOpaque){
      highBlock = getBlockAt(x, y--, z);
    }
  }else if(y > highestBlocks.get(x,z)){
    highestBlocks.get(x, z) = y;
  }
}

labo::minecraft::Block labo::minecraft::Chunk::getBlockAt(int x, int y, int z) {
  if(isOutOfBound(x,y,z)){
    return Air;
  }

  int bY = y % CHUNK_SIZE;

  return subChunks[y / CHUNK_SIZE].getBlock(x, bY, z);
}

int labo::minecraft::Chunk::getHeightAt(int x, int z) {
  return highestBlocks.get(x, z);
}

bool labo::minecraft::Chunk::hasLoaded() const noexcept {
  return isLoaded;
}

void labo::minecraft::Chunk::load(TerrainGenerator &generator){
  if(hasLoaded()){
    return;
  }

  generator.generateTerrainFor(*this);
  isLoaded = true;
}

labo::minecraft::SubChunk
&labo::minecraft::Chunk::getSubChunk(int index){
  static SubChunk errorSubChunk({444,444,444}, level);

  if(index >= subChunks.size() || index < 0){
    return errorSubChunk;
  }

  return subChunks[index];
}

void labo::minecraft::Chunk::addSubChunk() {
  int y = subChunks.size();
  subChunks.emplace_back(
    sf::Vector3i(location.x, y, location.y),
    level
    );
}

bool labo::minecraft::Chunk::isOutOfBound(
  int x, int y, int z) const {
  if(x >= CHUNK_SIZE){
    return true;
  }
  if(z >= CHUNK_SIZE){
    return true;
  }
  if(x < 0) return true;
  if(y < 0) return true;
  if(z < 0) return true;

  if(y >= (int)subChunks.size() * CHUNK_SIZE){
    return true;
  }

  return false;
}



