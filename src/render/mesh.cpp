#include "mesh.h"

labo::render::MeshContainer::
MeshContainer(const labo::render::Mesh &mesh) {
  addMesh(mesh);
}


labo::render::MeshContainer::MeshContainer(
  labo::render::MeshContainer &&other)
  : renderInfo(other.renderInfo)
  , vboCount(other.vboCount)
  , vboBuffer(std::move(other.vboBuffer))
{
  other.renderInfo.reset();
  other.vboCount = 0;
}

labo::render::MeshContainer
&labo::render::MeshContainer::operator=(MeshContainer &&other) {
  renderInfo = other.renderInfo;
  vboCount = other.vboCount;
  vboBuffer = std::move(other.vboBuffer);

  other.renderInfo.reset();
  other.vboCount = 0;

  return *this;
}

void labo::render::MeshContainer::addMesh(const labo::render::Mesh &mesh) {
  genVAO();

  addVBO(3, mesh.vertexPositions);
  addVBO(2, mesh.textureCoords);
  addEBO(mesh.indices);
}

void labo::render::MeshContainer::genVAO() {
  if(renderInfo.vao != 0){
    clean();
  }

  glGenVertexArrays(1, &renderInfo.vao);
  glBindVertexArray(renderInfo.vao);
}

void labo::render::MeshContainer::addEBO(const std::vector<GLuint> &indices) {
  renderInfo.indicesCount = static_cast<GLuint>(indices.size());
  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    indices.size() * sizeof(GLuint),
    indices.data(),
    GL_STATIC_DRAW
    );
}

void labo::render::MeshContainer::addVBO(
  int dimensions,
  const std::vector<GLfloat> &data) {
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER,
    data.size() * sizeof(GLfloat),
    data.data(),
    GL_STATIC_DRAW
    );
  glVertexAttribPointer(
    static_cast<GLuint>(vboCount),
    dimensions,
    GL_FLOAT,
    GL_FALSE,
    0,
    nullptr
    );
  glEnableVertexAttribArray(
    static_cast<GLuint>(vboCount++)
    );
  vboBuffer.push_back(vbo);
}

void labo::render::MeshContainer::bindVAO() const {
  glBindVertexArray(renderInfo.vao);
}

void labo::render::MeshContainer::clean() {
  if(renderInfo.vao){
    glDeleteVertexArrays(1, &renderInfo.vao);
  }
  if(!vboBuffer.empty()){
    glDeleteBuffers(
      static_cast<GLsizei>(vboBuffer.size()),
      vboBuffer.data()
      );
    vboBuffer.clear();
  }

  vboCount = 0;
  renderInfo.reset();
}

labo::render::MeshContainer::~MeshContainer() {
  clean();
}





