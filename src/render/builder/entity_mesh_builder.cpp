#include "entity_mesh_builder.h"
#include "../../minecraft/level/level.h"

labo::render::EntityMeshBuilder::EntityMeshBuilder(
  labo::minecraft::Level &level)
  : level(level)
{}

void labo::render::EntityMeshBuilder::buildMesh() {

  // さて、各情報をどこで管理しようか？ いまはぐちゃぐは
  // LevelMeshBuilderがChunkとEntityをビルドする
  // Entityに関する情報はEntityMeshBuilderに内包した方が良いのでは？

  // 新しいentityが追加されたら、Meshを新しく生成
  // もしentityが削除されたら、Meshを削除


  for(auto &entity: level.getEntities()){
  }
}
