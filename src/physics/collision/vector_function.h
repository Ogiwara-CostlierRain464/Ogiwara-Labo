#ifndef LABO_VECTOR_FUNCTION_H
#define LABO_VECTOR_FUNCTION_H

#include "../../math/glm.h"
#include "../base.h"

namespace labo::physics{

inline void calcTangentVector(
  const glm::vec3 &normal,
  glm::vec3 &tangent1,
  glm::vec3 &tangent2){
  glm::vec3 vec(1.f, 0.f, 0.f);
  glm::vec3 n(normal);
  n[0] = 0.0f;
  if(glm::length(n) < EPSILON){
    vec = glm::vec3(0, 1, 0);
  }
  // 衝突点の座標系の算出(P242)
  tangent1 = glm::normalize(glm::cross(normal, vec));
  tangent2 = glm::normalize(glm::cross(tangent1, normal));
}


}

#endif //LABO_VECTOR_FUNCTION_H
