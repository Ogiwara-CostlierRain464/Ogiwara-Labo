#ifndef LABO_ENTITY_RENDERER_H
#define LABO_ENTITY_RENDERER_H

#include <vector>
#include "../mesh/entity_mesh.h"
#include "../camera.h"
#include "../shader/entity_shader.h"

namespace labo::render{

class EntityRenderer {
public:
  void add(const EntityRenderInfo &renderInfo);
  void render(const Camera &camera);

private:
  std::vector<EntityRenderInfo> entityRenderInfos;

  EntityShader shader;
};

}

#endif //LABO_ENTITY_RENDERER_H
