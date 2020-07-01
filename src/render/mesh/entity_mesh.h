#ifndef LABO_ENTITY_MESH_H
#define LABO_ENTITY_MESH_H

#include "mesh.h"
#include "../../math/glm.h"

namespace labo::render{

class EntityMesh{
public:
  EntityMesh() = default;

  void addFace(
    const std::array<GLfloat, 12> &entityFace,
    const std::array<GLfloat, 8> &textureCoords,
    const glm::vec3 &position
    );

  void bufferMesh();

  void clean();

private:
  int faces = 0;
  Mesh mesh;
  MeshContainer meshContainer;
  std::vector<GLfloat> light;
  GLuint indexOffset = 0;

};

}

#endif //LABO_ENTITY_MESH_H
