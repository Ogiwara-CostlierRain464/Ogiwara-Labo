#include "water_renderer.h"
#include "../chunk_mesh.h"
#include "../camera.h"
#include "../opengl_debug.h"

void labo::render::WaterRenderer::add(
  const labo::render::ChunkMesh &mesh) {

  chunks.push_back(mesh.getContainer().getRenderInfo());
}

void labo::render::WaterRenderer::render(
  const labo::render::Camera &camera,
  float elapsedTime) {
  if(chunks.empty()){
    return;
  }

  checkGLError();

  glEnable(GL_BLEND);
  glDisable(GL_CULL_FACE);
  shader.useProgram();

  shader.loadProjViewMatrix(camera.getProjectionViewMatrix());
  shader.loadTime(elapsedTime);

  for(auto &mesh: chunks){
    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES, mesh.indicesCount, GL_UNSIGNED_INT, nullptr);
  }

  chunks.clear();
}
