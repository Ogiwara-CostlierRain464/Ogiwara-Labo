#ifndef LABO_WATER_RENDERER_H
#define LABO_WATER_RENDERER_H

#include <vector>
#include "../mesh/mesh.h"
#include "../shader/water_shader.h"

namespace labo::render{

class ChunkMesh;
class Camera;

class WaterRenderer{
public:
  void add(const ChunkMesh &mesh);
  void render(const Camera &camera, float elapsedTime);

private:
  std::vector<MeshContainer::RenderInfo> chunks;

  WaterShader shader;
};
}

#endif //LABO_WATER_RENDERER_H
