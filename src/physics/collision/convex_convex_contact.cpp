#include "convex_convex_contact.h"
#include "../base.h"
#include "closest_function.h"
#include <limits>
#include <chrono>
#include <iostream>

using glm::vec3;
using glm::mat3;
using glm::dot;
using glm::cross;
using glm::length;
using glm::normalize;
using labo::math::Transform3;
using labo::physics::Convex;
using labo::physics::EPSILON;
using labo::physics::ConvexMesh;

enum SatType{
  PointAFacetB,
  PointBFacetA,
  EdgeEdge
};

#define CHECK_MINMAX(axis, AMin, AMax, BMin, BMax, type) \
{\
  satCount++;\
  float d1 = AMin - BMax;\
	float d2 = BMin - AMax;\
	if(d1 >= 0.0f || d2 >= 0.0f) {\
		return false;\
	}\
	if(distanceMin < d1) {\
		distanceMin = d1;\
		axisMin = axis;\
		satType = type;\
		axisFlip = false;\
	}\
	if(distanceMin < d2) {\
		distanceMin = d2;\
		axisMin = -axis;\
		satType = type;\
		axisFlip = true;\
	}\
}

bool convexConvexContactLocal(
  const ConvexMesh &convexA,
  const labo::math::Transform3 &transformA,
  const ConvexMesh &convexB,
  const labo::math::Transform3 &transformB,
  vec3 &normal,
  float &penetrationDepth,
  vec3 &contactPointA,
  vec3 &contactPointB
  ){

  Transform3 transformAB{}, transformBA{};
  mat3 matrixAB, matrixBA;
  vec3 offsetAB, offsetBA;

  transformAB = transformA.inverse() * transformB;
  matrixAB = transformAB.getUpper3x3();
  offsetAB = transformAB.getTranslation();

  transformBA = transformAB.inverse();
  matrixBA = transformBA.getUpper3x3();
  offsetBA = transformBA.getTranslation();

  float distanceMin = - std::numeric_limits<float>::max();
  vec3 axisMin(0.f);
  SatType satType = EdgeEdge;
  bool axisFlip;

  // region 分離軸判定
  int satCount = 0;


  // ConvexAの面法線を分離軸とする
  for(size_t f=0; f < convexA.numFacets; f++){
    const auto &facet = convexA.facets[f];
    const auto separatingAxis = facet.normal;

    float minA, maxA;
    getProjection(minA, maxA, &convexA, separatingAxis);

    float minB, maxB;
    getProjection(minB, maxB, &convexB, matrixBA * facet.normal);
    float offset = dot(offsetAB,separatingAxis);
    minB += offset;
    maxB += offset;

    CHECK_MINMAX(separatingAxis, minA, maxA, minB, maxB, PointBFacetA);
  }


  // ConvexBの面法線を分離軸
  for(size_t f=0; f < convexB.numFacets; f++){
    const auto &facet = convexB.facets[f];
    const auto separatingAxis = matrixAB * facet.normal;

    float minA, maxA;
    getProjection(minA, maxA, &convexA, separatingAxis);

    float minB, maxB;
    getProjection(minB, maxB, &convexB, facet.normal);
    float offset = dot(offsetAB, separatingAxis);
    minB += offset;
    maxB += offset;

    CHECK_MINMAX(separatingAxis, minA, maxA, minB, maxB, PointAFacetB);
  }


  // ConvexAとConvexBのEdgeの外積を分離軸とする
  for(size_t eA =0; eA < convexA.numFacets; eA++){
    const auto &edgeA = convexA.edges[eA];
    if(edgeA.type != Convex) continue;

    const auto edgeVecA = convexA.vertices[edgeA.vertId[1]] - convexA.vertices[edgeA.vertId[0]];

    for(size_t eB =0; eB < convexB.numEdges; eB++){
      const auto &edgeB = convexB.edges[eB];
      if(edgeB.type != Convex) continue;

      const auto edgeVecB = matrixAB * (convexB.vertices[edgeB.vertId[1]] - convexB.vertices[edgeB.vertId[0]]);

      vec3 separatingAxis = cross(edgeVecA, edgeVecB);
      if(length(separatingAxis) < EPSILON * EPSILON) continue;

      separatingAxis = normalize(separatingAxis);

      float minA, maxA;
      getProjection(minA, maxA, &convexA, separatingAxis);

      float minB, maxB;
      getProjection(minB, maxB, &convexB, matrixBA * separatingAxis);
      float offset = dot(offsetAB, separatingAxis);
      minB += offset;
      maxB += offset;

      CHECK_MINMAX(separatingAxis, minA, maxA, minB, maxB, EdgeEdge);
    }
  }


  // endregion

  // ここまできたので衝突はしている

  int collCount = 0;
  float closestMinSqr = std::numeric_limits<float>::max();
  vec3 closestPointA, closestPointB;
  vec3 separation = 1.1f * abs(distanceMin) * axisMin;

  BENCH_START

  for(size_t fA = 0; fA < convexA.numFacets; fA++){
    const auto &facetA = convexA.facets[fA];

    float checkA = dot(facetA.normal, -axisMin);
    if(satType == PointBFacetA && checkA < 0.99f && axisFlip){
      continue;
    }

    if(checkA < 0.f){
      continue;
    }


    for(size_t fB = 0; fB < convexB.numFacets; fB++){
      const auto &facetB = convexB.facets[fB];

      float checkB = dot(facetB.normal, matrixBA * axisMin);
      if(satType == PointAFacetB && checkB < 0.99f && !axisFlip){
        continue;
      }

      if(checkB < 0.f){
        continue;
      }

      collCount++;

      vec3 triangleA[3] = {
        separation + convexA.vertices[facetA.vertId[0]],
        separation + convexA.vertices[facetA.vertId[1]],
        separation + convexA.vertices[facetA.vertId[2]]
      };

      vec3 triangleB[3] = {
        offsetAB + matrixAB * convexB.vertices[facetB.vertId[0]],
        offsetAB + matrixAB * convexB.vertices[facetB.vertId[1]],
        offsetAB + matrixAB * convexB.vertices[facetB.vertId[2]]
      };


      // エッジ同士の最近接点
      for(int i = 0; i < 3; i++){
        if(convexA.edges[facetA.edgeId[i]].type != Convex){continue;}

        for(int j=0; j<3; j++){
          if(convexB.edges[facetB.edgeId[j]].type != Convex){continue;}

          vec3 sA, sB;
          labo::physics::getClosestTwoSegments(
            triangleA[i], triangleA[(i+1)%3],
            triangleB[j], triangleB[(j+1)%3],
            sA, sB);

          float dSqr = length(sA - sB);
          if(dSqr < closestMinSqr){
            closestMinSqr = dSqr;
            closestPointA = sA;
            closestPointB = sB;
          }

        }
      }

      // 頂点A->面B
      for(int i=0; i<3; i++){
        vec3 s;
        labo::physics::getClosestPointTriangle(triangleA[i], triangleB[0], triangleB[1], triangleB[2], matrixAB * facetB.normal, s);
        float dSqr = length(triangleA[i] - s);
        if(dSqr < closestMinSqr){
          closestMinSqr = dSqr;
          closestPointA = triangleA[i];
          closestPointB = s;
        }
      }

      // 頂点B->面A
      for(int i=0; i<3; i++){
        vec3 s;
        labo::physics::getClosestPointTriangle(triangleB[i], triangleA[0], triangleA[1], triangleA[2], facetA.normal, s);
        float dSqr = length(triangleB[i] - s);
        if(dSqr < closestMinSqr){
          closestMinSqr = dSqr;
          closestPointA = s;
          closestPointB = triangleB[i];
        }
      }

    }

  }

  BENCH_END

  normal = transformA.getUpper3x3() * axisMin;
  penetrationDepth = distanceMin;
  contactPointA = closestPointA - separation;
  contactPointB = offsetBA + matrixBA * closestPointB;


  return true;
}

bool labo::physics::convexConvexContact(
  const ConvexMesh &convexA,
  const math::Transform3 &transformA,
  const ConvexMesh &convexB,
  const math::Transform3 &transformB,
  glm::vec3 &normal,
  float &penetrationDepth,
  glm::vec3 &contactPointA,
  glm::vec3 &contactPointB
){

  bool ret;
  if(convexA.numFacets >= convexB.numFacets){
    ret = convexConvexContactLocal(
      convexA, transformA,
      convexB, transformB,
      normal, penetrationDepth, contactPointA, contactPointB
      );
  }else{
    ret = convexConvexContactLocal(
      convexB, transformB,
      convexA, transformA,
      normal, penetrationDepth, contactPointB, contactPointA
    );
    normal = -normal;
  }

  return ret;
}