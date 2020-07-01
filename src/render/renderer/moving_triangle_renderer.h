#ifndef LABO_MOVING_TRIANGLE_RENDERER_H
#define LABO_MOVING_TRIANGLE_RENDERER_H

#include <glad/glad.h>
#include <vector>
#include "../mesh/mesh.h"
#include "../shader/shader.h"
#include "../camera.h"

namespace labo::render{

class MovingTriangleShader: public Shader{
public:
  MovingTriangleShader()
  : Shader("MoveTri", "MoveTri"){

    getUniforms();
  }

  void loadProjViewMatrix(const glm::mat4 &pvMat){
    loadMatrix4(locationProjViewMat, pvMat);
  }

private:
  void getUniforms()override {
    locationProjViewMat =
      glGetUniformLocation(programId, "projViewMatrix");
  }

  GLuint locationProjViewMat = 0;
};

class MovingTriangleRenderer{
public:
  MovingTriangleRenderer(){
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

  void render(const Camera &camera){
    shader.useProgram();
    shader.loadProjViewMatrix(camera.getProjectionViewMatrix());

    meshes.bindVAO();

    glDrawElements(GL_TRIANGLES, meshes.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
  }

private:
  MeshContainer meshes;
  MovingTriangleShader shader;
};

}

#endif //LABO_MOVING_TRIANGLE_RENDERER_H
