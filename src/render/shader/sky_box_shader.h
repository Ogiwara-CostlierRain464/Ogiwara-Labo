#ifndef LABO_SKY_BOX_SHADER_H
#define LABO_SKY_BOX_SHADER_H

#include "shader.h"

namespace labo::render{

class SkyBoxShader: public Shader{
public:
  SkyBoxShader()
    : Shader("SkyBox", "SkyBox")
  {
    getUniforms();
  }

  void loadViewMatrix(glm::mat4 viewMatrix){
    viewMatrix[3][0] = 0;
    viewMatrix[3][1] = 0;
    viewMatrix[3][2] = 0;
    Shader::loadMatrix4(locationView, viewMatrix);
  }

  void loadProjectionMatrix(const glm::mat4 &proj){
    Shader::loadMatrix4(locationProjection, proj);
  }

private:
  void getUniforms() override{
    locationProjection = glGetUniformLocation(id, "projectionMatrix");
    locationView = glGetUniformLocation(id, "viewMatrix");
  }

  GLuint locationProjection;
  GLuint locationView;
};

}

#endif //LABO_SKY_BOX_SHADER_H
