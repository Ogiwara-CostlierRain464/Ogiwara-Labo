#ifndef LABO_LEVEL_MESH_BUILDER_H
#define LABO_LEVEL_MESH_BUILDER_H

#include <unordered_map>
#include <memory>
#include "../chunk_mesh.h"
#include "../../math/vector_xz.h"
#include "../renderer/render_master.h"
#include "../../minecraft/level/format/chunk.h"


namespace labo::render{

class LevelMeshBuilder {
public:
  void buildAndPushToRenderer(
    labo::minecraft::Level &level,
    int renderDistance,
    Camera &camera,
    RenderMaster &renderMaster);

private:
  std::unordered_map<
    sf::Vector3i,
    std::unique_ptr<SubChunkMeshCollection>
    > meshCollections;

  void drawChunks(
    labo::minecraft::Chunk &chunk,
    RenderMaster &renderMaster,
    const Camera &camera
    );
};

}


#endif //LABO_LEVEL_MESH_BUILDER_H
