#ifndef LABO_MESH_H
#define LABO_MESH_H

#include <glad/glad.h>
#include <vector>


namespace labo::render{

/**
 * メッシュ情報を表す
 */
struct Mesh{
  std::vector<GLfloat> vertexPositions;
  std::vector<GLfloat> textureCoords;
  std::vector<GLuint> indices;

};

}

#endif //LABO_MESH_H
