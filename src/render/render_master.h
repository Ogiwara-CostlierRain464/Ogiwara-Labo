#ifndef LABO_RENDER_MASTER_H
#define LABO_RENDER_MASTER_H

#include <SFML/Graphics.hpp>
#include "camera.h"

namespace labo::render{
class RenderMaster {
public:
  void finish(sf::RenderWindow &window, const Camera &camera);
};
}

#endif //LABO_RENDER_MASTER_H
