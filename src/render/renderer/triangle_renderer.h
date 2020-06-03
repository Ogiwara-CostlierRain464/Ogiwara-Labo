#ifndef LABO_TRIANGLE_RENDERER_H
#define LABO_TRIANGLE_RENDERER_H

#include <glad/glad.h>
#include <vector>
#include "../mesh.h"
#include "../shader/triangle_shader.h"

namespace labo::render{

/**
 * Render basic triangle, just used for testing.
 */
class TriangleRenderer{
public:
  TriangleRenderer(){
    std::vector<GLfloat> vertices{
      0.f, 0.5f, // 0
      -0.5f, -0.5f, // 1
      0.5f, -0.5f // 2
    };

    std::vector<GLuint> indices{
      0,1,2
    };

    meshes.genVAO();
    meshes.addVBO(2, vertices);
    meshes.addEBO(indices);
  }

  void render(){
    shader.useProgram();
    meshes.bindVAO();
    glDrawElements(GL_TRIANGLES, meshes.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
  }

private:
  MeshCompound meshes;
  TriangleShader shader;
};

}

#endif //LABO_TRIANGLE_RENDERER_H
