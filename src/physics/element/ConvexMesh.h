#ifndef LABO_CONVEXMESH_H
#define LABO_CONVEXMESH_H

#include <cstdint>
#include <array>
#include "../../math/glm.h"

namespace {
  constexpr int CONVEX_MESH_MAX_VERTICES = 34;
  constexpr int CONVEX_MESH_MAX_EDGES = 96;
  constexpr int CONVEX_MESH_MAX_FACETS = 64;
}

namespace labo::physics{


enum EdgeType{
  // 凸
  Convex,
  // 凹
  Concave,
  // 平坦
  Flat
};

struct Edge{
  EdgeType type;
  // 端点の頂点インデックス
  std::array<uint8_t,2> vertId;
  // 共有する面インデックス
  std::array<uint8_t,2> facetId;
};

// 三角形面
struct Facet{
  // 頂点インデックス
  std::array<uint8_t,3> vertId;
  // エッジインデックス
  std::array<uint8_t,3> edgeId;
  // 面法線ベクトル
  glm::vec3 normal;
};

// 凸メッシュ
struct ConvexMesh{
  uint8_t  numVertices; // 頂点数
  uint8_t numFacets; // 面数
  uint8_t numEdges; // エッジ数
  std::array<glm::vec3, CONVEX_MESH_MAX_VERTICES> vertices;
  std::array<Edge, CONVEX_MESH_MAX_EDGES> edges;
  std::array<Facet, CONVEX_MESH_MAX_FACETS> facets;

  void reset(){
    numVertices = 0;
    numFacets = 0;
    numEdges = 0;
  }
};

void getProjection(
  float &pMin, float &pMax,
  const ConvexMesh *convexMesh,
  const glm::vec3 &axis
);

bool createConvexMesh(
  ConvexMesh *convexMesh,
  const float *vertices,
  uint32_t numVertices,
  const uint16_t *indices,
  uint32_t numIndices,
  const glm::vec3 &scale = glm::vec3(1.f)
);

}

#endif //LABO_CONVEXMESH_H
