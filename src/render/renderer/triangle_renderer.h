#ifndef LABO_TRIANGLE_RENDERER_H
#define LABO_TRIANGLE_RENDERER_H

#include <glad/glad.h>
#include <vector>
#include "../mesh.h"

namespace labo::render{

/**
 * Render basic triangle, just used for testing.
 */
class TriangleRenderer{
public:
  TriangleRenderer(){
    std::vector<GLfloat> vertices{
      0.f, 0.5f,
      0.5f, -0.5f,
      -0.5f, -0.5f
    };

    std::vector<GLuint> indices{
      0,1,2
    };

    meshes.genVAO();
    meshes.addVBO(2, vertices);
  }

  void render(){
    meshes.bindVAO();
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

private:
  MeshCompound meshes;
};

}

#endif //LABO_TRIANGLE_RENDERER_H
