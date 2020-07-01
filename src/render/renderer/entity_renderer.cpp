#include "entity_renderer.h"
#include "../block/block_database.h"

void labo::render::EntityRenderer::add(
  const labo::render::EntityRenderInfo &renderInfo) {
  entityRenderInfos.push_back(renderInfo);
}

void labo::render::EntityRenderer::render(
  const labo::render::Camera &camera) {

  if(entityRenderInfos.empty()){
    return;
  }

  glDisable(GL_BLEND);
  glEnable(GL_CULL_FACE);

  shader.useProgram();
  shader.loadProjViewMatrix(camera.getProjectionViewMatrix());

  BlockDatabase::get().textureAtlas.bindTexture();

  for(auto &renderInfo: entityRenderInfos){

    shader.loadPosition(renderInfo.position);
    shader.loadRotation(renderInfo.rotation);

    glBindVertexArray(renderInfo.renderInfo.vao);
    glDrawElements(GL_TRIANGLES, renderInfo.renderInfo.indicesCount, GL_UNSIGNED_INT, nullptr);
  }

  entityRenderInfos.clear();
}
