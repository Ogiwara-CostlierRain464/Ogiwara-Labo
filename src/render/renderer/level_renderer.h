#ifndef LABO_LEVEL_RENDERER_H
#define LABO_LEVEL_RENDERER_H

#include "../../minecraft/level/level.h"
#include "../../minecraft/level/format/chunk.h"
#include "../../math/vector_xz.h"
#include "../camera.h"
#include "../render_master.h"
#include "../chunk_mesh.h"
#include "../chunk_mesh_builder.h"

namespace labo::render{

// Method: MeshCollection vector per each sub chunk.
std::unordered_map<
  sf::Vector3i,
  std::unique_ptr<ChunkMeshCollection>> meshCollections;

void tryDrawChunks(
  labo::minecraft::Chunk &chunk,
  RenderMaster &renderMater,
  const Camera &camera
){

  for(auto &subChunk: chunk.getSubChunks()){

    // 更新があると、再度Bufferする必要がある
    // 結局のところ、毎回VAOを元にrender命令を出せばよいだけ
    /**
     * - has_mesh: 常にtrue
     * - has_buffered_mesh: 更新があるとfalseに
     *
     * レンダリング時に
     *
     * 更新があると:
     * - has_buffered_meshがfalseになっているので
     * - バッファされ、
     * - has_buffered_meshがtrueに
     *
     * 更新がないと:
     * - has_buffered_meshがtrueになっているので、そのままrenderする
     *
     * これを変えると
     * SubChunkにはisUpdatedを作り
     *
     * ChunkMeshCollectionを管理し、
     *
     * - isUpdated==true:
     * - バッファする
     * - isUpdated = false
     * - render
     *
     * - isUpdated==false:
     * - render
     */

    if(meshCollections.count(subChunk.getLocation()) == 0){
      auto ptr = std::make_unique<ChunkMeshCollection>();
      meshCollections.emplace(subChunk.getLocation(), std::move(ptr));
    }


    auto &ptr = meshCollections.at(subChunk.getLocation());

    if(subChunk.needRender){
      ChunkMeshBuilder(&subChunk, ptr.get()).buildMesh();
      ptr->solidMesh.bufferMesh();
      subChunk.needRender = false;
    }

    if(camera.getFrustum().isBoxInFrustum(subChunk.getAABB())){
      renderMater.drawChunk(*ptr.get());
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
