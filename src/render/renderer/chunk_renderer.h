#ifndef LABO_CHUNK_RENDERER_H
#define LABO_CHUNK_RENDERER_H

#include "../chunk_mesh.h"

namespace labo::render{
class ChunkRenderer {
public:
  void add(const ChunkMesh &mesh);
  void render();


};
}

#endif //LABO_CHUNK_RENDERER_H
