#include "entity_mesh.h"
#include <array>

void labo::render::EntityMesh::addFace(
  const std::array<GLfloat, 12> &entityFace,
  const std::array<GLfloat, 8> &textureCoords,
  const glm::vec3 &position) {

  auto &vertices = mesh.vertexPositions;
  auto &texCoords = mesh.textureCoords;
  auto &indices = mesh.indices;

  texCoords.insert(
    texCoords.end(),
    textureCoords.begin(),
    textureCoords.end());

  size_t index = 0;
  for(size_t i = 0; i <= 3; i++){
    vertices.push_back(
      entityFace[index++]
      + position.x
      );

    vertices.push_back(
      entityFace[index++]
      + position.y
    );

    vertices.push_back(
      entityFace[index++]
      + position.z
    );

    light.push_back(1);
  }

  indices.insert(
    indices.end(),
    {indexOffset, indexOffset + 1, indexOffset + 2,
     indexOffset + 2, indexOffset + 3, indexOffset});

  indexOffset += 4;

  faces++;
}

void labo::render::EntityMesh::bufferMesh() {
  meshContainer.addMesh(mesh);
  meshContainer.addVBO(1, light);

  mesh.clearAll();
  light.clear();
  light.shrink_to_fit();

  indexOffset = 0;
}

void labo::render::EntityMesh::clean() {
  meshContainer.clean();
}
