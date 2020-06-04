#ifndef LABO_LEVEL_RENDERER_H
#define LABO_LEVEL_RENDERER_H

#include "../../minecraft/level/level.h"
#include "../../minecraft/level/format/chunk.h"
#include "../../math/vector_xz.h"
#include "../camera.h"
#include "../render_master.h"

namespace labo::render{

void tryDrawChunks(
  labo::minecraft::Chunk &chunk,
  RenderMaster &renderMater,
  Camera &camera
){
  for(auto &subChunk: chunk.getSubChunks()){
    // meshを構成する代わりに、need_renderとかで置き換えよう

    // 更新必要なら
      // バッファされてないなら
        // バッファする
     // 描画範囲内なら
      // 描画chunkリストについか
      // さて、消費されるQueueなのか固定されるQueueなのか意識しないとね

    // Meshを作るべき条件
    // ブロックの更新があったsection
    // すでに上でマークされておらず、カメラの視野体に入るsub chunk

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
