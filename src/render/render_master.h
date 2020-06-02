#ifndef LABO_RENDER_MASTER_H
#define LABO_RENDER_MASTER_H

#include <SFML/Graphics.hpp>
#include "camera.h"
#include "renderer/sky_box_renderer.h"

namespace labo::render{
class RenderMaster {
public:
  void finish(sf::Window &window, const Camera &camera);


private:
  SkyBoxRenderer skyBoxRenderer;
};
}

#endif //LABO_RENDER_MASTER_H
