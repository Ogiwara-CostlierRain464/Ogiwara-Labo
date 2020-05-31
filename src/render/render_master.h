#ifndef LABO_RENDER_MASTER_H
#define LABO_RENDER_MASTER_H

#include <SFML/Graphics.hpp>
#include "camera.h"
#include "renderer/sfml_renderer.h"

namespace labo::render{
class RenderMaster {
public:
  void drawSFML(const sf::Drawable &drawable);
  void finish(sf::RenderWindow &window, const Camera &camera);

private:
  SFMLRenderer sfmlRenderer;
};
}

#endif //LABO_RENDER_MASTER_H
