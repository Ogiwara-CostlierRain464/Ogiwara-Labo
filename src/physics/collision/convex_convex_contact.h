#ifndef LABO_CONVEX_CONVEX_CONTACT_H
#define LABO_CONVEX_CONVEX_CONTACT_H

#include "../../math/glm.h"
#include "../element/ConvexMesh.h"

namespace labo::physics{

// 二つの凸メッシュの衝突検知
bool convexConvexContact(
  const ConvexMesh &convexA,
  const math::Transform3 &transformA,
  const ConvexMesh &convexB,
  const math::Transform3 &transformB,
  glm::vec3 &normal,
  float &penetrationDepth,
  glm::vec3 &contactPointA,
  glm::vec3 &contactPointB
);

}


#endif //LABO_CONVEX_CONVEX_CONTACT_H
