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

#endif //LABO_FLORA_SHADER_H
