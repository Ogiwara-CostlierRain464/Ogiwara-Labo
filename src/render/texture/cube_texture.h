#ifndef LABO_CUBE_TEXTURE_H
#define LABO_CUBE_TEXTURE_H

#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include "../../math/non_copyable.h"
#include <array>
#include <string>

namespace labo::render{

class CubeTexture: public math::NonCopyable{
public:
  CubeTexture() = default;
  explicit CubeTexture(const std::array<std::string, 6> &files){
    loadFromFiles(files);
  }

  ~CubeTexture(){
    glDeleteTextures(1, &textureId);
  }

  /**
   * Must be in this order:
   * - right
   * - left
   * - top
   * - bottom
   * - back
   * - front
   */
  void loadFromFiles(const std::array<std::string, 6> &files){
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    for(int i = 0; i < 6; i++){
      auto &str = files[i];

      sf::Image image;
      if(!image.loadFromFile("res/textures/" + str + ".png")){
        throw std::runtime_error("Unable to load CubeTexture Part: " + str);
      }

      auto param = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
      auto width = image.getSize().x;
      auto height = image.getSize().y;

      glTexImage2D(param, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  void bindTexture()const {
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
  }

private:
  GLuint textureId = 0;
};

}

#endif //LABO_CUBE_TEXTURE_H
