#ifndef LABO_ENTITY_MESH_BUILDER_H
#define LABO_ENTITY_MESH_BUILDER_H

#include "../../minecraft/level/format/chunk.h"

namespace labo::render{
class EntityMeshBuilder {
public:
  explicit EntityMeshBuilder(labo::minecraft::Chunk &chunk);

  void buildMesh();

private:
  labo::minecraft::Chunk &chunk;
};
}

#endif //LABO_ENTITY_MESH_BUILDER_H
