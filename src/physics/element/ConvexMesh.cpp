#include "ConvexMesh.h"
#include <limits>
#include "../base.h"

using namespace std;
using namespace glm;


void labo::physics::getProjection(
  float &pMin, float &pMax,
  const ConvexMesh *convexMesh,
  const glm::vec3 &axis
){
  assert(convexMesh);

  float pMin_ = numeric_limits<float>::max();
  float pMax_ = -numeric_limits<float>::max();

  for(size_t i =0; i < convexMesh->numVertices; i++){
    float prj = glm::dot(axis, convexMesh->vertices[i]);
    pMin_ = std::min(pMin_, prj);
    pMax_ = std::max(pMax_, prj);
  }

  pMin = pMin_;
  pMax = pMax_;
}

bool labo::physics::createConvexMesh(
  ConvexMesh *convexMesh,
  const float *vertices,
  uint32_t numVertices,
  const uint16_t *indices,
  uint32_t numIndices,
  const glm::vec3 &scale
){
  assert(convexMesh);
  assert(vertices);
  assert(indices);
  assert(dot(scale, scale) > 0.f);

  if(numVertices > CONVEX_MESH_MAX_VERTICES || numIndices > CONVEX_MESH_MAX_FACETS * 3){
    return false;
  }

  memset(convexMesh, 0, sizeof(ConvexMesh));

  for(size_t i=0; i < numVertices; i++){
    convexMesh->vertices[i][0] = vertices[i * 3];
    convexMesh->vertices[i][1] = vertices[i*3+1];
    convexMesh->vertices[i][2] = vertices[i*3+2];
    convexMesh->vertices[i] = mulPerElem(scale, convexMesh->vertices[i]);
  }
  convexMesh->numVertices = numVertices;

  uint32_t nf = 0;
  for(size_t i=0; i < numIndices/3; i++){
    vec3 p[] = {
      convexMesh->vertices[indices[i*3]],
      convexMesh->vertices[indices[i*3+1]],
      convexMesh->vertices[indices[i*3+2]]
    };

    vec3 normal = cross(p[1]-p[0], p[2]-p[0]);
    float areaSqr = length(normal);
    if(areaSqr > EPSILON * EPSILON){
      convexMesh->facets[nf].vertId[0] = (uint8_t) indices[i*3];
      convexMesh->facets[nf].vertId[1] = (uint8_t) indices[i*3+1];
      convexMesh->facets[nf].vertId[2] = (uint8_t) indices[i*3+2];
      convexMesh->facets[nf].normal = normal / sqrtf(areaSqr);
      nf++;
    }
  }
  convexMesh->numFacets = nf;

  uint8_t edgeIdTable[CONVEX_MESH_MAX_VERTICES*CONVEX_MESH_MAX_VERTICES/2];
  memset(edgeIdTable, 0xff, sizeof(edgeIdTable));

  uint32_t ne = 0;
  for(size_t i=0; i < convexMesh->numFacets; i++){
    auto &facet = convexMesh->facets[i];
    for(size_t e=0; e < 3; e++){
      auto vertId0 = std::min(facet.vertId[e%3], facet.vertId[(e+1)%3]);
      auto vertId1 = std::max(facet.vertId[e%3], facet.vertId[(e+1)%3]);
      auto tableId = vertId1 * (vertId1-1)/2 + vertId0;
      if(edgeIdTable[tableId] == 0xff){
        // 初回時は登録のみ
        convexMesh->edges[ne].facetId[0] = i;
        convexMesh->edges[ne].facetId[1] = i;
        convexMesh->edges[ne].vertId[0] = (uint8_t) vertId0;
        convexMesh->edges[ne].vertId[1] = (uint8_t) vertId1;
        convexMesh->edges[ne].type = Convex;
        facet.edgeId[e] = ne;
        edgeIdTable[tableId] = ne;
        ne++;
        if(ne > CONVEX_MESH_MAX_EDGES){
          return false;
        }
      }else{
        assert(edgeIdTable[tableId] < CONVEX_MESH_MAX_EDGES);
        auto &edge = convexMesh->edges[edgeIdTable[tableId]];
        auto &facetB = convexMesh->facets[edge.facetId[0]];

        assert(edge.facetId[0] == edge.facetId[1]);

        vec3 s = convexMesh->vertices[facet.vertId[(e+2)%3]];
        vec3 q = convexMesh->vertices[facetB.vertId[0]];
        float d = dot(s-q, facetB.normal);

        if(d < -EPSILON){
          edge.type = Convex;
        }else if (d > EPSILON){
          // ここに来てはいけない
          assert(false);
          edge.type = Concave;
        }else{
          edge.type = Flat;
        }

        edge.facetId[1] = i;
      }
    }
  }

  convexMesh->numEdges = ne;

  return true;
}