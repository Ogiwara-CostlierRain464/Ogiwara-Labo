#ifndef LABO_MESH_H
#define LABO_MESH_H

#include <glad/glad.h>
#include <vector>
#include "../../math/non_copyable.h"


namespace labo::render{

/**
 * 多角形の集まりで表された形状データを表す
 */
struct Mesh{
  std::vector<GLfloat> vertexPositions;
  std::vector<GLfloat> textureCoords;
  std::vector<GLuint> indices;

  void clearAll(){
    vertexPositions.clear();
    vertexPositions.shrink_to_fit();
    textureCoords.clear();
    textureCoords.shrink_to_fit();
    indices.clear();
    indices.shrink_to_fit();
  }
};

/**
 * VAO,VBO,EBOを保持するコンテナ
 * NOTE: 適切な名前に変えよう
 *
 */
class MeshContainer: public labo::math::NonCopyable{
public:
  /**
   * 描画に必要な情報を格納
   */
  struct RenderInfo{
    GLuint vao = 0;
    GLuint indicesCount = 0;

    inline void reset(){
      vao = 0;
      indicesCount = 0;
    }
  };

  MeshContainer() = default;
  explicit MeshContainer(const Mesh &mesh);
  ~MeshContainer();

  MeshContainer(MeshContainer &&other);
  MeshContainer &operator=(MeshContainer &&other);

  void addMesh(const Mesh &mesh);
  void clean();

  void genVAO();
  void addEBO(const std::vector<GLuint> &indices);
  void addVBO(int dimensions, const std::vector<GLfloat> &data);
  // 現在のコンテキストにVAOを設定する
  void bindVAO() const;

  [[nodiscard]]
  int getIndicesCount()const {
    return renderInfo.indicesCount;
  }

  [[nodiscard]]
  RenderInfo getRenderInfo()const {
    return renderInfo;
  }

private:
  RenderInfo renderInfo;
  int vboCount = 0;
  std::vector<GLuint> vboBuffer;
};

}

#endif //LABO_MESH_H
