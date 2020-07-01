#ifndef LABO_CHUNK_RENDERER_H
#define LABO_CHUNK_RENDERER_H

#include "../mesh/chunk_mesh.h"
#include "../camera.h"
#include "../shader/chunk_shader.h"

namespace labo::render{
class ChunkRenderer {
public:
  void add(const ChunkMesh &mesh);
  void render(const Camera &camera);

private:
  std::vector<MeshContainer::RenderInfo> chunks;

  ChunkShader shader;
};
}

#endif //LABO_CHUNK_RENDERER_H
