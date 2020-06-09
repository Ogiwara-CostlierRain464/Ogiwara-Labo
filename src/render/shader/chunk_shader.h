#ifndef LABO_CHUNK_SHADER_H
#define LABO_CHUNK_SHADER_H

#include "shader.h"

namespace labo::render{
class ChunkShader: public Shader{
public:
  ChunkShader()
    : Shader("Chunk", "Chunk"){
    getUniforms();
  }

  void loadProjViewMatrix(const glm::mat4 &pvMat){
    loadMatrix4(locationProjViewMat, pvMat);
  }

private:
  void getUniforms()override {
    //useProgram();
    locationProjViewMat =
      glGetUniformLocation(id, "projViewMatrix");
  }

  GLuint locationProjViewMat;
};

}

#endif //LABO_CHUNK_SHADER_H
