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

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,renderInfo.position);
    model = glm::rotate(model, renderInfo.rotation.x, {1,0,0});
    model = glm::rotate(model, renderInfo.rotation.y, {0,1,0});
    model = glm::rotate(model, renderInfo.rotation.z, {0,0,1});

    shader.loadModel(model);

    glBindVertexArray(renderInfo.renderInfo.vao);
    glDrawElements(GL_TRIANGLES, renderInfo.renderInfo.indicesCount, GL_UNSIGNED_INT, nullptr);
  }

  entityRenderInfos.clear();
}
