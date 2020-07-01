#ifndef LABO_ENTITY_SHADER_H
#define LABO_ENTITY_SHADER_H

#include "shader.h"

namespace labo::render{
class EntityShader: public Shader{
public:
  EntityShader()
  : Shader("Entity", "Entity"){
    getUniforms();
  }

  void loadProjViewMatrix(const glm::mat4 &pvMat){
    loadMatrix4(locationProjViewMat, pvMat);
  }

  void loadModel(const glm::mat4 &model){
    loadMatrix4(locationModel, model);
  }

private:
  void getUniforms() override{
    locationProjViewMat =
      glGetUniformLocation(programId, "projViewMatrix");
    locationModel =
      glGetUniformLocation(programId, "model");
  }

  GLuint locationProjViewMat = 0;
  GLuint locationModel = 0;
};
}

#endif //LABO_ENTITY_SHADER_H
