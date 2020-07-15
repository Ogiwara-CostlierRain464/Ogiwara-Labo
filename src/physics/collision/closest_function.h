#ifndef LABO_CLOSEST_FUNCTION_H
#define LABO_CLOSEST_FUNCTION_H

#include "../../math/glm.h"

namespace labo::physics{

// 二つの線分の最近接点検出
void getClosestTwoSegments(
  const glm::vec3 &segmentPointA0,
  const glm::vec3 &segmentPointA1,
  const glm::vec3 &segmentPointB0,
  const glm::vec3 &segmentPointB1,
  glm::vec3 &closestPointA,
  glm::vec3 &closestPointB
);

// 頂点から三角形面への最近接点検出
void getClosestPointTriangle(
  const glm::vec3 &point,
  const glm::vec3 &trianglePoint0,
  const glm::vec3 &trianglePoint1,
  const glm::vec3 &trianglePoint2,
  const glm::vec3 &triangleNormal,
  glm::vec3 &closestPoint
);

}

#endif //LABO_CLOSEST_FUNCTION_H
