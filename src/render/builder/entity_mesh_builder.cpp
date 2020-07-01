#include "entity_mesh_builder.h"
#include "../../minecraft/level/level.h"
#include "../block/block_database.h"

// At first use same faces as chunk_mesh_builder
namespace{
  const std::array<GLfloat, 12> frontFace{
    0,0,1,
    1,0,1,
    1,1,1,
    0,1,1
  };

  const std::array<GLfloat, 12> backFace{
    1, 0, 0,
    0, 0, 0,
    0, 1, 0,
    1, 1, 0,
  };

  const std::array<GLfloat, 12> leftFace{
    0, 0, 0,
    0, 0, 1,
    0, 1, 1,
    0, 1, 0,
  };

  const std::array<GLfloat, 12> rightFace{
    1, 0, 1,
    1, 0, 0,
    1, 1, 0,
    1, 1, 1,
  };

  const std::array<GLfloat, 12> topFace{
    0, 1, 1,
    1, 1, 1,
    1, 1, 0,
    0, 1, 0,
  };

  const std::array<GLfloat, 12> bottomFace{
    0, 0, 0,
    1, 0, 0,
    1, 0, 1,
    0, 0, 1
  };
}

labo::render::EntityMeshBuilder::EntityMeshBuilder(
  labo::minecraft::Level &level)
  : level(level)
{}

void labo::render::EntityMeshBuilder::buildMesh(RenderMaster &renderMaster) {

  // さて、各情報をどこで管理しようか？ いまはぐちゃぐは
  // LevelMeshBuilderがChunkとEntityをビルドする
  // Entityに関する情報はEntityMeshBuilderに内包した方が良いのでは？

  // 新しいentityが追加されたら、Meshを新しく生成
  // もしentityが削除されたら、Meshを削除


  // 頂点情報は変わらず、常に位置と回転情報を受け取る

  for(auto &entity: level.getEntities()){
    if(meshes.count(entity->id) == 0){
      meshes.emplace(entity->id, EntityMesh());

      auto &entityMesh = meshes.at(entity->id);

      auto appear = BlockDatabase::get().getBlockAppearance(6);
      auto texCoords = BlockDatabase::get().textureAtlas.getTexture(appear.texTopCoord);

      // EntityのVAOの位置自体は0にしておく。
      // Shaderのuniformで位置と回転を調節
      glm::vec3 base = {0,0,0};

      entityMesh.addFace(
        frontFace,
        texCoords,
        base
        );

      entityMesh.addFace(
        backFace,
        texCoords,
        base
      );

      entityMesh.addFace(
        leftFace,
        texCoords,
        base
      );

      entityMesh.addFace(
        rightFace,
        texCoords,
        base
      );

      entityMesh.addFace(
        topFace,
        texCoords,
        base
      );

      entityMesh.addFace(
        bottomFace,
        texCoords,
        base
      );

      entityMesh.bufferMesh();
    }

    auto &entityMesh = meshes.at(entity->id);

    EntityRenderInfo info{
      entityMesh.getContainer().getRenderInfo(),
      entity->position,
      entity->rotation
    };

    renderMaster.drawEntity(info);
  }
}
