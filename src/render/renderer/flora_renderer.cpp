#include "flora_renderer.h"
#include "../mesh/chunk_mesh.h"
#include "../camera.h"

void labo::render::FloraRenderer::add(
  const ChunkMesh &mesh){
  chunks.push_back(mesh.getContainer().getRenderInfo());
}

void labo::render::FloraRenderer::render(
  const Camera &camera, float elapsedTime) {
  if(chunks.empty()){
    return;
  }

  glDisable(GL_BLEND);
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
