#ifndef LABO_SHADER_H
#define LABO_SHADER_H

#include <glad/glad.h>
#include "../../math/non_copyable.h"
#include "../../math/glm.h"
#include <string>

namespace labo::render{
class Shader : public labo::math::NonCopyable{
public:
  Shader(
    const std::string &vertexFile,
    const std::string &fragmentFile
    );

  virtual ~Shader();

  void useProgram();

  void loadInt(GLuint location, int value);
  void loadFloat(GLuint location, float value);
  void loadVector2(GLuint location, const glm::vec2 &vec);
  void loadVector3(GLuint location, const glm::vec3 &vec);
  void loadVector4(GLuint location, const glm::vec4 &vec);
  void loadMatrix4(GLuint location, const glm::mat4 &matrix);

  GLuint programId;
protected:
  virtual void getUniforms() = 0;
//  GLuint id;
};

}
#endif //LABO_SHADER_H
