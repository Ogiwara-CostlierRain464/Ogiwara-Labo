#ifndef LABO_LEVEL_MESH_BUILDER_H
#define LABO_LEVEL_MESH_BUILDER_H

#include <unordered_map>
#include <memory>
#include "../mesh/chunk_mesh.h"
#include "../../math/vector_xz.h"
#include "../renderer/render_master.h"
#include "../../minecraft/level/format/chunk.h"
#include "entity_mesh_builder.h"


namespace labo::render{

class LevelMeshBuilder {
public:
  LevelMeshBuilder(labo::minecraft::Level &level, RenderMaster &renderMaster);

  void buildAndPushToRenderer(
    int renderDistance,
    Camera &camera);

private:
  labo::minecraft::Level &level;
  RenderMaster &renderMaster;
  EntityMeshBuilder entityMeshBuilder;

  std::unordered_map<
    sf::Vector3i,
    std::unique_ptr<SubChunkMeshCollection>
    > meshCollections;


  void drawChunks(
    labo::minecraft::Chunk &chunk,
    const Camera &camera
    );
};


}


#endif //LABO_LEVEL_MESH_BUILDER_H
