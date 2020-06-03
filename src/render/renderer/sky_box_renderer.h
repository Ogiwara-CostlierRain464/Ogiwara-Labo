#ifndef LABO_SKY_BOX_RENDERER_H
#define LABO_SKY_BOX_RENDERER_H

#include "../camera.h"
#include "../mesh.h"
#include "../shader/sky_box_shader.h"
#include "../texture/cube_texture.h"

namespace labo::render{

/**
 * ユーザーの周りに空を描画する
 */
class SkyBoxRenderer {
public:
  SkyBoxRenderer();

  void render(const Camera &camera);

private:
  MeshContainer skyCube;
  SkyBoxShader shader;
  CubeTexture cubeTexture;
};

}


#endif //LABO_SKY_BOX_RENDERER_H
