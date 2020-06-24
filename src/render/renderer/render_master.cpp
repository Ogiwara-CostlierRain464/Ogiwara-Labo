#include "render_master.h"
#include "../opengl_debug.h"

#include <glad/glad.h>


void labo::render::RenderMaster::drawChunk(
  const SubChunkMeshCollection &collection) {
  const auto &solidMesh = collection.solidMesh;
  const auto &waterMesh = collection.waterMesh;
  const auto &floraMesh = collection.floraMesh;
  const auto &entityMesh = collection.entityMesh;

  if(solidMesh.faces > 0){
    chunkRenderer.add(solidMesh);
  }
  chunkRenderer.add(entityMesh);

  if(waterMesh.faces > 0){
    waterRenderer.add(waterMesh);
  }
  if(floraMesh.faces > 0){
    floraRenderer.add(floraMesh);
  }
}


void labo::render::RenderMaster::finish(
  sf::Window &window,
  const Camera &camera,
  float elapsedTime) {
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  //triangleRenderer.render();
  //textRenderer.render();

  chunkRenderer.render(camera);
  waterRenderer.render(camera, elapsedTime);
  floraRenderer.render(camera, elapsedTime);


  glDisable(GL_CULL_FACE);
  skyBoxRenderer.render(camera);
  movingTriangleRenderer.render(camera);

  checkGLError();

  window.display();
}