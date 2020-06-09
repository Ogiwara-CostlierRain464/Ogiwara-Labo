#ifndef LABO_TEXTURE_ATLAS_H
#define LABO_TEXTURE_ATLAS_H

#include "basic_texture.h"

namespace labo::render{
class TextureAtlas: public BasicTexture{
public:
  explicit TextureAtlas(const std::string &textureFileName);

  std::array<GLfloat, 8> getTexture(const sf::Vector2i &coords);

private:
  int imageSize;
  int individualTextureSize;
};
}


#endif //LABO_TEXTURE_ATLAS_H
