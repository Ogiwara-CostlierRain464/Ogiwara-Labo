#include "chunk_mesh.h"
#include "../../minecraft/level/const.h"

using labo::minecraft::CHUNK_SIZE;

void labo::render::ChunkMesh::addFace(
  const std::array<GLfloat, 12> &blockFace,
  const std::array<GLfloat, 8> &textureCoords,
  const sf::Vector3i &chunkPosition,
  const sf::Vector3i &blockPosition,
  GLfloat cardinalLight) {
  auto &vertices = mesh.vertexPositions;
  auto &texCoords = mesh.textureCoords;
  auto &indices = mesh.indices;

  texCoords.insert(
    texCoords.end(),
    textureCoords.begin(),
    textureCoords.end());

  int index = 0;
  for(int i = 0; i <= 3; i++ ){
    vertices.push_back(
      blockFace[index++]
      + chunkPosition.x * CHUNK_SIZE
      + blockPosition.x
      );

    vertices.push_back(
      blockFace[index++]
      + chunkPosition.y * CHUNK_SIZE
      + blockPosition.y
    );

    vertices.push_back(
      blockFace[index++]
      + chunkPosition.z * CHUNK_SIZE
      + blockPosition.z
    );

    light.push_back(cardinalLight);
  }

  indices.insert(
    indices.end(),
    {indexOffset, indexOffset + 1, indexOffset + 2,
     indexOffset + 2, indexOffset + 3, indexOffset});

  indexOffset += 4;

  faces++;
}

void labo::render::ChunkMesh::bufferMesh() {
  meshContainer.addMesh(mesh);
  meshContainer.addVBO(1, light);

  mesh.clearAll();
  light.clear();
  light.shrink_to_fit();

  indexOffset = 0;
}

void labo::render::ChunkMesh::clean() {
  meshContainer.clean();
}
