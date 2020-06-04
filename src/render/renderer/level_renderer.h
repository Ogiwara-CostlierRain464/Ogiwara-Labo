#ifndef LABO_LEVEL_RENDERER_H
#define LABO_LEVEL_RENDERER_H

#include "../../minecraft/level/level.h"
#include "../../minecraft/level/format/chunk.h"
#include "../../math/vector_xz.h"
#include "../camera.h"
#include "../render_master.h"
#include "../chunk_mesh.h"

namespace labo::render{

struct AdjacentBlockPositions{
  sf::Vector3i up;
  sf::Vector3i down;
  sf::Vector3i left;
  sf::Vector3i right;
  sf::Vector3i front;
  sf::Vector3i back;

  void update(int x, int y, int z){
    up = {x, y + 1, z};
    down = {x, y - 1, z};
    left = {x - 1, y, z};
    right = {x + 1, y, z};
    front = {x, y, z + 1};
    back = {x, y, z - 1};
  }
};

void tryDrawSubChunk(
  RenderMaster &renderMaster,
  labo::minecraft::SubChunk &subChunk
  ){
//  // make mesh
//  ChunkMeshCollection meshCollection;
//
//  // buildMesh() come here
//  AdjacentBlockPositions directions;
//  int faces = 0;
//  auto blockPtr = subChunk.blocksFirstPtr();
//  for(int i =0; i < labo::minecraft::CHUNK_VOLUME; i++){
//    int x = i % labo::minecraft::CHUNK_VOLUME;
//    int y = i / (labo::minecraft::CHUNK_AREA);
//    int z = (i / labo::minecraft::CHUNK_SIZE) % labo::minecraft::CHUNK_SIZE;
//
//
//  }

}

void tryDrawChunks(
  labo::minecraft::Chunk &chunk,
  RenderMaster &renderMater,
  const Camera &camera
){
  for(auto &subChunk: chunk.getSubChunks()){
    // 更新必要なら
      // バッファされてないなら
        // バッファする
     // 描画範囲内なら
      // 描画chunkリストについか
      // さて、消費されるQueueなのか固定されるQueueなのか意識しないとね

    // Meshを作るべき条件
    // ブロックの更新があったsection
    // すでに上でマークされておらず、カメラの視野体に入るsub chunk
    if(subChunk.isNeedRender()){
      if(camera.getFrustum().isBoxInFrustum(subChunk.getAABB())){
        tryDrawSubChunk(renderMater, subChunk);
      }
    }

  }
}

void tryRender(
  labo::minecraft::Level &level,
  Camera &camera,
  int renderDistance,
  RenderMaster &renderMater
  ){
  // render sub_chunk, chunk, level
  auto &chunkManager = level.getChunkManager();
  auto &chunkMap = chunkManager.getChunks();

  for(auto itr = chunkMap.begin(); itr != chunkMap.end();){
    auto &chunk = itr->second;

    int cameraX = camera.getPosition().x;
    int cameraZ = camera.getPosition().z;

    int minX = (cameraX / labo::minecraft::CHUNK_SIZE) - renderDistance;
    int minZ = (cameraZ / labo::minecraft::CHUNK_SIZE) - renderDistance;
    int maxX = (cameraX / labo::minecraft::CHUNK_SIZE) + renderDistance;
    int maxZ = (cameraZ / labo::minecraft::CHUNK_SIZE) + renderDistance;

    auto location = chunk.getLocation();

    if(minX > location.x
    || minZ > location.y
    || maxZ < location.y
    || maxX < location.x){
      itr = chunkMap.erase(itr);
      continue;
    }else{
      // render chunk
      tryDrawChunks(chunk, renderMater, camera);

      itr++;
    }
  }
}

}

#endif //LABO_LEVEL_RENDERER_H
