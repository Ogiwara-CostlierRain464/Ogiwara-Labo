#ifndef LABO_OPENGL_DEBUG_H
#define LABO_OPENGL_DEBUG_H

#include <glad/glad.h>
#include <stdexcept>
#include <string>
/**
 * Useful functions for checking OpenGL error.
 */
namespace labo::render{

void checkGLError(){
  GLenum err;
  while((err = glGetError())!= GL_NO_ERROR )
  {
    throw std::runtime_error("OpenGL error: ");
  }
}

void checkShaderError(GLuint shaderID){
  GLint isSuccess = 0;
  GLchar infoLog[512];

  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
  if(!isSuccess){
    glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
    throw std::runtime_error("Error occurred while load shader: " + std::string(infoLog));
  }
}
}

#endif //LABO_OPENGL_DEBUG_H
