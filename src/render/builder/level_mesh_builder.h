#ifndef LABO_LEVEL_MESH_BUILDER_H
#define LABO_LEVEL_MESH_BUILDER_H

#include "../renderer/render_master.h"
#include "../../minecraft/level/format/chunk.h"

namespace labo::render{

class LevelMeshBuilder {
public:
  static void buildAndPushToRenderer(
    labo::minecraft::Level &level,
    int renderDistance,
    Camera &camera,
    RenderMaster &renderMaster);

private:
  static void drawChunks(
    labo::minecraft::Chunk &chunk,
    RenderMaster &renderMaster,
    const Camera &camera
    );


};

}


#endif //LABO_LEVEL_MESH_BUILDER_H
