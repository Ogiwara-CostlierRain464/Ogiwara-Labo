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

  void loadModelMatrix(const glm::mat4 &mat){
    loadMatrix4(locationModelMat, mat);
  }

private:
  void getUniforms()override {
    locationProjViewMat = glGetUniformLocation(id, "projViewMatrix");
    locationModelMat = glGetUniformLocation(id, "modelMatrix");
  }

  GLuint locationProjViewMat;
  GLuint locationModelMat;
};

}

#endif //LABO_CHUNK_SHADER_H
