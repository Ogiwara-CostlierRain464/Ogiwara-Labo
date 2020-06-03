#include "sky_box_renderer.h"
#include "../opengl_debug.h"

labo::render::SkyBoxRenderer::SkyBoxRenderer(){
  constexpr GLfloat SIZE = 500;
  std::vector<GLfloat> vertexCoors{
    // Back
    SIZE,
    -SIZE,
    -SIZE,
    -SIZE,
    -SIZE,
    -SIZE,
    -SIZE,
    SIZE,
    -SIZE,
    SIZE,
    SIZE,
    -SIZE,

    // Front
    -SIZE,
    -SIZE,
    SIZE,
    SIZE,
    -SIZE,
    SIZE,
    SIZE,
    SIZE,
    SIZE,
    -SIZE,
    SIZE,
    SIZE,

    // Right
    SIZE,
    -SIZE,
    SIZE,
    SIZE,
    -SIZE,
    -SIZE,
    SIZE,
    SIZE,
    -SIZE,
    SIZE,
    SIZE,
    SIZE,

    // Left
    -SIZE,
    -SIZE,
    -SIZE,
    -SIZE,
    -SIZE,
    SIZE,
    -SIZE,
    SIZE,
    SIZE,
    -SIZE,
    SIZE,
    -SIZE,

    // Top
    -SIZE,
    SIZE,
    SIZE,
    SIZE,
    SIZE,
    SIZE,
    SIZE,
    SIZE,
    -SIZE,
    -SIZE,
    SIZE,
    -SIZE,

    // Bottom
    -SIZE,
    -SIZE,
    -SIZE,
    SIZE,
    -SIZE,
    -SIZE,
    SIZE,
    -SIZE,
    SIZE,
    -SIZE,
    -SIZE,
    SIZE,
  };

  std::vector<GLuint> indices{
    0,  1,  2,  2,  3,  0,
    4,  5,  6,  6,  7,  4,
    8,  9,  10, 10, 11, 8,
    12, 13, 14, 14, 15, 12,
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 20
  };

  skyCube.genVAO();
  skyCube.addVBO(3, vertexCoors);
  skyCube.addEBO(indices);

  cubeTexture.loadFromFiles({
     "dm",
     "dm",
     "dt",
     "db",
     "dm",
     "dm",
   });
}

void labo::render::SkyBoxRenderer::render(const Camera &camera) {
  shader.useProgram();
  skyCube.bindVAO();
  cubeTexture.bindTexture();

  shader.loadViewMatrix(camera.getViewMatrix());
  shader.loadProjectionMatrix(camera.getProjMatrix());

  glDrawElements(GL_TRIANGLES, skyCube.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
  checkGLError();
}
