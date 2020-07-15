#include "closest_function.h"
#include "../base.h"

using glm::vec3;
using glm::mat3;
using glm::dot;
using glm::cross;

void labo::physics::getClosestTwoSegments(
  const glm::vec3 &segmentPointA0,
  const glm::vec3 &segmentPointA1,
  const glm::vec3 &segmentPointB0,
  const glm::vec3 &segmentPointB1,
  glm::vec3 &closestPointA,
  glm::vec3 &closestPointB
){
  vec3 v1 = segmentPointA1 - segmentPointA0;
  vec3 v2 = segmentPointB1 - segmentPointB0;
  vec3 r = segmentPointA0 - segmentPointB0;

  float a = dot(v1, v1);
  float b = dot(v1, v2);
  float c = dot(v2, v2);
  float d = dot(v1, r);
  float e = dot(v2, r);
  float det = -a*c+b*b;
  float s = 0.f, t = 0.f;

  if(det*det > EPSILON){
    s = (c*d-b*e)/det;
  }

  s = clamp(s, 0.f, 1.f);
  t = (e+s*b)/c;
  t = clamp(t, 0.f, 1.f);
  s = (-d+t*b)/a;
  s = clamp(s, 0.f, 1.f);
  closestPointA = segmentPointA0 + s * v1;
  closestPointB = segmentPointB0 + t * v2;
}

static inline void getClosestPointLine(
  const vec3 &point,
  const vec3 &linePoint,
  const vec3 &lineDirection,
  vec3 &closestPoint
  ){
  float s = dot(point - linePoint, lineDirection) / dot(lineDirection, lineDirection);
  closestPoint = linePoint + s * lineDirection;
}

void labo::physics::getClosestPointTriangle(
  const glm::vec3 &point,
  const glm::vec3 &trianglePoint0,
  const glm::vec3 &trianglePoint1,
  const glm::vec3 &trianglePoint2,
  const glm::vec3 &triangleNormal,
  glm::vec3 &closestPoint
){
  vec3 proj = point - dot(triangleNormal, point - trianglePoint0) * triangleNormal;

  // Voronoi area of edge P0,P1
  vec3 edgeP01 = trianglePoint1 - trianglePoint0;
  vec3 edgeP01_normal = cross(edgeP01, triangleNormal);

  float voronoiEdgeP01_check1 = dot(proj - trianglePoint0, edgeP01_normal);
  float voronoiEdgeP01_check2 = dot(proj - trianglePoint0, edgeP01);
  float voronoiEdgeP01_check3 = dot(proj - trianglePoint1, -edgeP01);

  if(voronoiEdgeP01_check1 > 0.f && voronoiEdgeP01_check2 > 0.f && voronoiEdgeP01_check3 > 0.f){
    getClosestPointLine(trianglePoint0, edgeP01, proj, closestPoint);
    return;
  }

  // Voronoi area of edge P1,P2
  vec3 edgeP12 = trianglePoint2 - trianglePoint1;
  vec3 edgeP12_normal = cross(edgeP12, triangleNormal);

  float voronoiEdgeP12_check1 = dot(proj - trianglePoint1, edgeP12_normal);
  float voronoiEdgeP12_check2 = dot(proj - trianglePoint1, edgeP12);
  float voronoiEdgeP12_check3 = dot(proj - trianglePoint2, -edgeP12);

  if(voronoiEdgeP12_check1 > 0.f && voronoiEdgeP12_check2 > 0.f && voronoiEdgeP12_check3 > 0.f){
    getClosestPointLine(trianglePoint1, edgeP12, proj, closestPoint);
    return;
  }

  // Voronoi area of edge P2,P0
  vec3 edgeP20 = trianglePoint0 - trianglePoint2;
  vec3 edgeP20_normal = cross(edgeP20, triangleNormal);

  float voronoiEdgeP20_check1 = dot(proj - trianglePoint2, edgeP20_normal);
  float voronoiEdgeP20_check2 = dot(proj - trianglePoint2, edgeP20);
  float voronoiEdgeP20_check3 = dot(proj - trianglePoint0, -edgeP20);

  if(voronoiEdgeP20_check1 > 0.f && voronoiEdgeP20_check2 > 0.f && voronoiEdgeP20_check3 > 0.f){
    getClosestPointLine(trianglePoint2, edgeP20, proj, closestPoint);
    return;
  }

  // 三角形面の内側
  if(voronoiEdgeP01_check1 <= 0.f && voronoiEdgeP12_check1 <= 0.f && voronoiEdgeP20_check1 <= 0.f){
    closestPoint = proj;
    return;
  }

  // 頂点P0のボロノイ
  if(voronoiEdgeP01_check2 <= 0.f && voronoiEdgeP20_check3 <= 0.f){
    closestPoint = trianglePoint0;
    return;
  }

  // 頂点P1のボロノイ
  if(voronoiEdgeP01_check3 <= 0.f && voronoiEdgeP12_check2 <= 0.f){
    closestPoint = trianglePoint1;
    return;
  }

  // 頂点P2のボロノイ
  if(voronoiEdgeP20_check2 <= 0.f && voronoiEdgeP12_check3 <= 0.f){
    closestPoint = trianglePoint2;
    return;
  }

  //assert(false);
}