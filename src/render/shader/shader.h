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


  static void loadInt(GLuint location, int value);
  static void loadFloat(GLuint location, float value);
  static void loadVector2(GLuint location, const glm::vec2 &vec);
  static void loadVector3(GLuint location, const glm::vec3 &vec);
  static void loadVector4(GLuint location, const glm::vec4 &vec);
  static void loadMatrix4(GLuint location, const glm::mat4 &matrix);

protected:
  virtual void getUniforms() = 0;
  GLuint id;
};

}
#endif //LABO_SHADER_H
