#ifndef LABO_RENDER_MASTER_H
#define LABO_RENDER_MASTER_H

#include <SFML/Graphics.hpp>
#include "camera.h"
#include "renderer/sky_box_renderer.h"
#include "renderer/triangle_renderer.h"
#include "renderer/moving_triangle_renderer.h"

namespace labo::render{
class RenderMaster {
public:
  void finish(sf::Window &window, const Camera &camera);


private:
  SkyBoxRenderer skyBoxRenderer;
  TriangleRenderer triangleRenderer;
  MovingTriangleRenderer movingTriangleRenderer;
};
}

#endif //LABO_RENDER_MASTER_H
