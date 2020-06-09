#include "chunk_renderer.h"
#include "../opengl_debug.h"
#include "../block/block_database.h"

void labo::render::ChunkRenderer::add(
  const labo::render::ChunkMesh &mesh) {

  chunks.push_back(mesh.getContainer().getRenderInfo());

}

void labo::render::ChunkRenderer::render(
  const Camera &camera) {

  if(chunks.empty()){
    return;
  }

  glDisable(GL_BLEND);
  //glEnable(GL_CULL_FACE);

  shader.useProgram();
  shader.loadProjViewMatrix(camera.getProjectionViewMatrix());
  BlockDatabase::get().textureAtlas.bindTexture();

  //checkGLError();
  //checkShaderError(shader.id);

  for(auto &mesh : chunks) {
    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES, mesh.indicesCount, GL_UNSIGNED_INT, nullptr);
  }

  //checkGLError();

  chunks.clear();
}

