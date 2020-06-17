#include "level_mesh_builder.h"
#include "../../minecraft/level/level.h"
#include "chunk_mesh_builder.h"

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
  for(auto &subChunk: chunk.getSubChunks()){
    if(meshCollections.count(subChunk.getLocation()) == 0){
      auto ptr = std::make_unique<ChunkMeshCollection>();
      meshCollections.emplace(subChunk.getLocation(), std::move(ptr));
    }

    auto &ptr = meshCollections.at(subChunk.getLocation());

    if(subChunk.isUpdated){
      ChunkMeshBuilder(&subChunk, ptr.get()).buildMesh();
      ptr->solidMesh.bufferMesh();
      subChunk.isUpdated = false;
    }

    if(camera.getFrustum().isBoxInFrustum(subChunk.getAABB())){
      renderMaster.drawChunk(*ptr.get());
    }
  }
}
