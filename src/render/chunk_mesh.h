#ifndef LABO_CHUNK_MESH_H
#define LABO_CHUNK_MESH_H

#include "mesh.h"
#include <array>
#include <SFML/System.hpp>

namespace labo::render{
/**
 * ChunkのMeshを表す
 */
class ChunkMesh {
public:
  ChunkMesh() = default;

  void addFace(
    const std::array<GLfloat, 12> &blockFace,
    const std::array<GLfloat, 8> &textureCoords,
    const sf::Vector3i &chunkPosition,
    const sf::Vector3i &blockPosition,
    GLfloat cardinalLight
    );

  void bufferMesh();
  void clean();


private:
  int faces = 0;
  // ここでは各座標をBufferするものとして働く
  Mesh mesh;
  MeshCompound meshCompound;
  std::vector<GLfloat> light;
  // NOTE: rename better name
  GLuint indexOffset = 0;
};

struct ChunkMeshCollection{
  ChunkMesh solidMesh;
  ChunkMesh waterMesh;
  ChunkMesh floraMesh;
};

}


#endif //LABO_CHUNK_MESH_H
