#ifndef LABO_FLORA_RENDERER_H
#define LABO_FLORA_RENDERER_H

#include <vector>
#include "../mesh/mesh.h"
#include "../shader/flora_shader.h"

namespace labo::render{

class ChunkMesh;
class Camera;

class FloraRenderer {
public:
  void add(const ChunkMesh &mesh);
  void render(const Camera &camera, float elapsedTime);

private:
  std::vector<MeshContainer::RenderInfo> chunks;
  FloraShader shader;
};

}

#endif //LABO_FLORA_RENDERER_H
