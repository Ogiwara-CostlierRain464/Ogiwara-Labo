#include "render_master.h"

#include <glad/glad.h>

void labo::render::RenderMaster::finish(
  sf::Window &window,
  const Camera &camera) {
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  //triangleRenderer.render();
  //textRenderer.render();


  glDisable(GL_CULL_FACE);
  skyBoxRenderer.render(camera);
  //movingTriangleRenderer.render(camera);




  window.display();
}