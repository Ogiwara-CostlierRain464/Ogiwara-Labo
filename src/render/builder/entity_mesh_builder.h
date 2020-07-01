#ifndef LABO_ENTITY_MESH_BUILDER_H
#define LABO_ENTITY_MESH_BUILDER_H

#include <unordered_map>
#include "../../minecraft/level/format/chunk.h"
#include "../../minecraft/entity/entity.h"
#include "../../math/id.h"

namespace labo::render{
class EntityMeshBuilder {
public:
  explicit EntityMeshBuilder(labo::minecraft::Level &level);

  void buildMesh();

private:
  labo::minecraft::Level &level;
  std::unordered_map<math::Id<minecraft::Entity>, >
};
}

#endif //LABO_ENTITY_MESH_BUILDER_H
