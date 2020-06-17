#include "level_mesh_builder.h"
#include "../../minecraft/level/level.h"

void labo::render::LevelMeshBuilder::buildAndPushToRenderer(
  labo::minecraft::Level &level,
  int renderDistance,
  Camera &camera,
  RenderMaster &renderMaster) {
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
      drawChunks(chunk, renderMaster, camera);

      itr++;
    }
  }

}

void labo::render::LevelMeshBuilder::drawChunks(
  labo::minecraft::Chunk &chunk,
  RenderMaster &renderMaster,
  const Camera &camera) {

}
