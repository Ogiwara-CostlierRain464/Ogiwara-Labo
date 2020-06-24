#include "entity_mesh_builder.h"
#include "../../minecraft/level/level.h"

labo::render::EntityMeshBuilder::EntityMeshBuilder(
  labo::minecraft::Level &level)
  : level(level)
{}

void labo::render::EntityMeshBuilder::buildMesh() {
  for(auto &entity: level.getEntities()){

  }
}
