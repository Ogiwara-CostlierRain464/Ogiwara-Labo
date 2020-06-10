#ifndef LABO_OPENGL_DEBUG_H
#define LABO_OPENGL_DEBUG_H

#include <glad/glad.h>
#include <stdexcept>
#include <string>
/**
 * Useful functions for checking OpenGL error.
 */
namespace labo::render{

/**
 * @see https://www.khronos.org/opengl/wiki/OpenGL_Error
 */
static void checkGLError(){
  GLenum err;
  while((err = glGetError())!= GL_NO_ERROR )
  {
    std::string message = "OpenGL error: " + std::to_string(err);
    throw std::runtime_error(message);
  }
}

static void checkShaderError(GLuint shaderID){
  GLint isSuccess = 0;

  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
  if(!isSuccess){
    GLint maxLength = 0;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

    std::string s(errorLog.begin(), errorLog.end());

    perror(s.c_str());
    throw std::runtime_error(
      "Error occurred while load shader: " + s
      );
  }
}
}

#endif //LABO_OPENGL_DEBUG_H
