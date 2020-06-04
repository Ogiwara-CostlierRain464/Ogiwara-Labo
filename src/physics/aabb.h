#ifndef LABO_AABB_H
#define LABO_AABB_H
#include "../math/glm.h"

namespace labo::physics{
struct AABB {
  // AABBのoffset
  glm::vec3 position;
  // 原点に対する幅
  glm::vec3 dimensions;

  void updatePosition(const glm::vec3 &pos) {
    position = pos;
  }

  glm::vec3 getVP(const glm::vec3 &normal) const{
    glm::vec3 res = position;
    if(normal.x > 0){
      res.x += dimensions.x;
    }
    if(normal.y > 0){
      res.y += dimensions.y;
    }
    if(normal.z > 0){
      res.z += dimensions.z;
    }

    return res;
  }
};
}

#endif //LABO_AABB_H
