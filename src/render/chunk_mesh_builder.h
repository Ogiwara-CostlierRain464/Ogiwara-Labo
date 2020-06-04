#ifndef LABO_CHUNK_MESH_BUILDER_H
#define LABO_CHUNK_MESH_BUILDER_H

#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include "../minecraft/block/block.h"
#include "../minecraft/level/format/sub_chunk.h"

namespace labo::render{

class ChunkMesh;
class ChunkMeshCollection;

class ChunkMeshBuilder {
public:
  ChunkMeshBuilder(labo::minecraft::SubChunk *subChunk, ChunkMeshCollection *collection);

  void buildMesh();

private:
  void setActiveMesh(labo::minecraft::Block block);
  void addXBlockToMesh(
    const sf::Vector2i &textureCoords,
    const sf::Vector3i &blockPosition
    );

  void tryAddFaceToMesh(
    const std::array<GLfloat, 12> &blockFace,
    const sf::Vector2i &textureCoords,
    const sf::Vector3i &blockPosition,
    const sf::Vector3i &blockFacing,
    GLfloat cardinalLight
    );

  bool shouldMakeFace(
    const sf::Vector3i &blockPosition
  );

  bool shouldMakeLayer(int y);

  int faces = 0;
  const labo::minecraft::Block *block;
  labo::minecraft::SubChunk *subChunk;
  ChunkMeshCollection *collection;
  ChunkMesh *activeMesh;
};
}



#endif //LABO_CHUNK_MESH_BUILDER_H
