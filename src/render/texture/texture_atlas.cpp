#include "texture_atlas.h"
#include <array>

labo::render::TextureAtlas::TextureAtlas(
  const std::string &textureFileName) :
  BasicTexture(textureFileName) {
  sf::Image i;
  if(i.loadFromFile("res/textures/" + textureFileName + ".png")){
    throw std::runtime_error("Unable to open image: " + textureFileName);
  }
  loadFromImage(i);

  imageSize = 256;
  individualTextureSize = 16;
}

std::array<GLfloat, 8> labo::render::TextureAtlas::getTexture(
  const sf::Vector2i &coords) {
  static const GLfloat TEX_PRE_ROW =
    (GLfloat) imageSize / (GLfloat) individualTextureSize;
  static const GLfloat INDIVIDUAL_TEX_SIZE = 1.f / TEX_PRE_ROW;
  static const GLfloat PIXEL_SIZE = 1.f / (float) imageSize;

  GLfloat xMin = (coords.x * INDIVIDUAL_TEX_SIZE) + 0.5f * PIXEL_SIZE;
  GLfloat yMin = (coords.y * INDIVIDUAL_TEX_SIZE) + 0.5f * PIXEL_SIZE;

  GLfloat xMax = (xMin + INDIVIDUAL_TEX_SIZE) - PIXEL_SIZE;
  GLfloat yMax = (yMin + INDIVIDUAL_TEX_SIZE) - PIXEL_SIZE;

  return {xMax, yMax, xMin, yMax, xMin, yMin, xMax, yMin};
}

