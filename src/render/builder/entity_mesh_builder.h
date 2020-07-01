#ifndef LABO_ENTITY_MESH_BUILDER_H
#define LABO_ENTITY_MESH_BUILDER_H

#include <unordered_map>
#include "../../minecraft/level/format/chunk.h"
#include "../../minecraft/entity/entity.h"
#include "../../math/id.h"
#include "../mesh/entity_mesh.h"
#include "../renderer/render_master.h"

namespace labo::render{
class EntityMeshBuilder {
public:
  explicit EntityMeshBuilder(labo::minecraft::Level &level);

  void buildMesh(RenderMaster &renderMaster);

private:
  labo::minecraft::Level &level;
  std::unordered_map<
  math::Id<minecraft::Entity>,EntityMesh> meshes;
};
}

#endif //LABO_ENTITY_MESH_BUILDER_H
