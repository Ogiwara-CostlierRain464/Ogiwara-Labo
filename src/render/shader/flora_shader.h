#ifndef LABO_FLORA_SHADER_H
#define LABO_FLORA_SHADER_H

#include "shader.h"

namespace labo::render{

class FloraShader: public Shader{
public:
  FloraShader()
    : Shader("Flora", "Chunk"){
    getUniforms();
  }

  void loadProjViewMatrix(const glm::mat4 &pvMat){
    loadMatrix4(locationProjViewMat, pvMat);
  }

  void loadTime(const float &time_){
    loadFloat(time, time_);
  }

protected:
  GLuint time;
  GLuint locationProjViewMat;

  void getUniforms() override {
    time = glGetUniformLocation(id, "globalTime");
    locationProjViewMat =
      glGetUniformLocation(id, "projViewMatrix");
  }
};

}

#endif //LABO_FLORA_SHADER_H
