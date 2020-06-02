#include "render_master.h"

#include <glad/glad.h>



void labo::render::RenderMaster::finish(
  sf::RenderWindow &window,
  const labo::render::Camera &camera) {
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  //sfmlRenderer.render(window);
}
