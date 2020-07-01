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

  [[nodiscard]]
  const MeshContainer &getContainer(){
    return meshContainer;
  }

private:
  int faces = 0;
  Mesh mesh;
  MeshContainer meshContainer;
  std::vector<GLfloat> light;
  GLuint indexOffset = 0;

};

/**
 * Entityの描画に必要な情報を格納
 */
struct EntityRenderInfo{
  MeshContainer::RenderInfo renderInfo;
  glm::vec3 position;
  glm::vec3 rotation;
};

}

#endif //LABO_ENTITY_MESH_H
