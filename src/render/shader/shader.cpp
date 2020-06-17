#include "shader.h"
#include "shader_loader.h"
#include "../opengl_debug.h"

labo::render::Shader::Shader(
  const std::string &vertexFile,
  const std::string &fragmentFile)
{
  id = loadShaders(vertexFile, fragmentFile);
  useProgram();
}

labo::render::Shader::~Shader() {
  glDeleteProgram(id);
}

void labo::render::Shader::useProgram() {
  glUseProgram(id);
}

void labo::render::Shader::loadInt(GLuint location, int value) {
  glUniform1i(location, value);
}

void labo::render::Shader::loadFloat(GLuint location, float value) {
  glUniform1f(location, value);
}

void labo::render::Shader::loadVector2(GLuint location, const glm::vec2 &vec) {
  glUniform2f(location, vec.x, vec.y);
}

void labo::render::Shader::loadVector3(GLuint location, const glm::vec3 &vec) {
  glUniform3f(location, vec.x, vec.y, vec.z);
}

void labo::render::Shader::loadVector4(GLuint location, const glm::vec4 &vec) {
  glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void labo::render::Shader::loadMatrix4(GLuint location, const glm::mat4 &matrix) {
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}





