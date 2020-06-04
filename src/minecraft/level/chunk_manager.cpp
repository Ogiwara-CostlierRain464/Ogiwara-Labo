#include "chunk_manager.h"
#include "format/chunk.h"

using labo::math::VectorXZ;
using labo::minecraft::Chunk;

labo::minecraft::ChunkManager::ChunkManager(
  labo::minecraft::Level &level)
  : level(level)
{
//  //とりあえず適用なChunkを作る
//  Chunk chunk(&level, {0,0});
//  chunk.getSubChunks()[0].setBlock(1,1,1,Stone);
//  chunks.emplace(VectorXZ{0,0}, chunk);
}

labo::minecraft::Chunk &labo::minecraft::ChunkManager::getChunk(int x, int z) {
  VectorXZ key{x,z};
  if(!isChunkExistAt(x,z)){
    Chunk chunk{&level, {x,z}};
    chunks.emplace(key, std::move(chunk));
  }

  return chunks[key];
}

std::unordered_map<labo::math::VectorXZ, Chunk> &labo::minecraft::ChunkManager::getChunks() {
  return chunks;
}

bool labo::minecraft::ChunkManager::isChunkLoadedAt(int x, int z) const {
  if(isChunkExistAt(x,z))
    return false;

  return chunks.at({x,z}).hasLoaded();
}

bool labo::minecraft::ChunkManager::isChunkExistAt(int x, int z) const {
  return chunks.find({x,z}) != chunks.end();
}








