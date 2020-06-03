#ifndef LABO_MOVING_TRIANGLE_RENDERER_H
#define LABO_MOVING_TRIANGLE_RENDERER_H

#include <glad/glad.h>
#include <vector>
#include "../mesh.h"
#include "../shader/shader.h"
#include "../camera.h"

namespace labo::render{

class MovingTriangleShader: public Shader{
public:
  MovingTriangleShader(): Shader("MoveTri", "MoveTri"){
    getUniforms();
  }

  void loadViewMatrix(glm::mat4 viewMatrix){
    viewMatrix[3][0] = 0;
    viewMatrix[3][1] = 0;
    viewMatrix[3][2] = 0;
    loadMatrix4(locationView, viewMatrix);
  }

  void loadProjectionMatrix(const glm::mat4 &proj){
    loadMatrix4(locationProjection, proj);
  }

private:
  void getUniforms()override {
    locationProjection = glGetUniformLocation(id, "projectionMatrix");
    locationView = glGetUniformLocation(id, "viewMatrix");
  }

  GLuint locationProjection = 0;
  GLuint locationView = 0;
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
    meshes.bindVAO();

    shader.loadViewMatrix(camera.getViewMatrix());
    shader.loadProjectionMatrix(camera.getProjMatrix());

    glDrawElements(GL_TRIANGLES, meshes.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
  }

private:
  MeshCompound meshes;
  MovingTriangleShader shader;
};

}

#endif //LABO_MOVING_TRIANGLE_RENDERER_H
