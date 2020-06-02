#ifndef LABO_SKY_BOX_RENDERER_H
#define LABO_SKY_BOX_RENDERER_H

#include "../camera.h"
#include "../mesh.h"

namespace labo::render{

/**
 *
 */
class SkyBoxRenderer {
public:
  SkyBoxRenderer();

  void render(const Camera &camera);

private:
  MeshCompound skyCube;

};

}


#endif //LABO_SKY_BOX_RENDERER_H
