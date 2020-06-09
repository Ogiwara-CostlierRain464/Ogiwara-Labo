#ifndef LABO_CHUNK_MESH_BUILDER_H
#define LABO_CHUNK_MESH_BUILDER_H

#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include "../minecraft/block/block.h"
#include "../minecraft/level/format/sub_chunk.h"
#include "block/block_appearance.h"

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
    const sf::Vector3i &blockPosition,
    const BlockAppearance &blockAppear
  );

  bool shouldMakeLayer(int y);

  int faces = 0;
  const labo::minecraft::Block *blockPtr = nullptr;
  labo::minecraft::SubChunk *subChunk = nullptr;
  ChunkMeshCollection *collection = nullptr;
  ChunkMesh *activeMesh = nullptr;
  const BlockAppearance *blockAppearPtr = nullptr;
};
}



#endif //LABO_CHUNK_MESH_BUILDER_H
