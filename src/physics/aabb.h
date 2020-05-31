#ifndef LABO_AABB_H
#define LABO_AABB_H
#include "../math/glm.h"

namespace labo::physics{
struct AABB {
  // AABBのoffset
  glm::vec3 position;
  // 原点に対する幅
  const glm::vec3 dimensions;

  void updatePosition(const glm::vec3 &pos) {
    position = pos;
  }
};
}

#endif //LABO_AABB_H
