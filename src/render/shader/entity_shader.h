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

  void loadPosition(const glm::vec3 &pos){
    loadVector3(locationPosition, pos);
  }

  void loadRotation(const glm::vec3 &rot){
    loadVector3(locationRotation, rot);
  }

private:
  void getUniforms() override{
    locationProjViewMat =
      glGetUniformLocation(programId, "projViewMatrix");
    locationPosition =
      glGetUniformLocation(programId, "position");
    locationRotation =
      glGetUniformLocation(programId, "rotation");
  }

  GLuint locationProjViewMat = 0;
  GLuint locationPosition = 0;
  GLuint locationRotation = 0;
};
}

#endif //LABO_ENTITY_SHADER_H
