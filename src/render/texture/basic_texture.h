#ifndef LABO_BASIC_TEXTURE_H
#define LABO_BASIC_TEXTURE_H

#include <glad/glad.h>
#include "../../math/non_copyable.h"
#include <string>
#include <SFML/Graphics.hpp>


namespace labo::render{

class BasicTexture: public labo::math::NonCopyable{
public:
  explicit BasicTexture(const std::string &file){
    loadFromFile(file);
  }

  ~BasicTexture(){
    glDeleteTextures(1, &textureId);
  }

  void loadFromImage(const sf::Image &image){
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RGBA,
      image.getSize().x, image.getSize().y, 0,
      GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
  }

  void loadFromFile(const std::string &file){
    sf::Image i;
    if(!i.loadFromFile("res/textures/" + file + ".png")){
      throw std::runtime_error("Unable to load BasicTexture: " + file);
    }

    loadFromImage(i);
  }

  void bindTexture() const{
    glBindTexture(GL_TEXTURE_2D, textureId);
  }

private:
  GLuint textureId = 0;
};

}

#endif //LABO_BASIC_TEXTURE_H
