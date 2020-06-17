#ifndef LABO_WATER_SHADER_H
#define LABO_WATER_SHADER_H

#include "shader.h"

namespace labo::render{

class WaterShader: public Shader{
public:
  WaterShader(): Shader("Water", "Chunk"){
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

#endif //LABO_WATER_SHADER_H
