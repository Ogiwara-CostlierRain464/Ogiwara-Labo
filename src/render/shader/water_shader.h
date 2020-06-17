#ifndef LABO_WATER_SHADER_H
#define LABO_WATER_SHADER_H

#include "shader.h"

namespace labo::render{

class WaterShader: public Shader{
public:
  WaterShader(): Shader("Water", "Chunk"){
    getUniforms();
  }

  void loadTime(const float &time_){
    loadFloat(time, time_);
  }

protected:
  GLuint time;
  void getUniforms() override {
    time = glGetUniformLocation(id, "globalTime");
  }
};

}

#endif //LABO_WATER_SHADER_H
