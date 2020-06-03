#ifndef LABO_TRIANGLE_SHADER_H
#define LABO_TRIANGLE_SHADER_H

#include "shader.h"

namespace labo::render{

class TriangleShader: public Shader{
public:
  TriangleShader(): Shader("Triangle", "Triangle"){
    //getUniforms();
  }

private:
  void getUniforms() override {
    ;
  }

};

}

#endif //LABO_TRIANGLE_SHADER_H
