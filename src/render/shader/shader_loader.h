#ifndef LABO_SHADER_LOADER_H
#define LABO_SHADER_LOADER_H

#include <string>
#include "../opengl_debug.h"
#include "../../math/file.h"
#include <glad/glad.h>

namespace labo::render{

GLuint compileShader(const GLchar *source, GLenum shaderType){
  auto shaderId = glCreateShader(shaderType);

  glShaderSource(shaderId, 1, &source, nullptr);
  glCompileShader(shaderId);

  checkShaderError(shaderId);
  return shaderId;
}

GLuint linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID){
  auto id = glCreateProgram();
  glAttachShader(id, vertexShaderID);
  glAttachShader(id, fragmentShaderID);

  glLinkProgram(id);
  return id;
}

GLuint loadShaders(
  const std::string &vertexShader,
  const std::string &fragmentShader
){
  auto vertexSource =
    labo::math::getFileContents("shaders/" + vertexShader + ".vert");
  auto fragmentSource =
    labo::math::getFileContents("shaders/" + fragmentShader + ".frag");

  auto vertexShaderID =
    compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
  auto fragmentShaderID =
    compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

  auto shaderID = linkProgram(vertexShaderID, fragmentShaderID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  return shaderID;
}

}

#endif //LABO_SHADER_LOADER_H
