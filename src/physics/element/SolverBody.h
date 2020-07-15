#ifndef LABO_SOLVERBODY_H
#define LABO_SOLVERBODY_H

#include "../../math/glm.h"

namespace labo::physics{

struct SolverBody{
  // 並進速度差分
  glm::vec3 deltaLinearVelocity;
  // 回転速度差分
  glm::vec3 deltaAngularVelocity;
  // 姿勢
  glm::quat orientation;
  // 慣性テンソルの逆行列
  glm::mat3 inertiaInv;
  // 質量の逆数
  float massInv;
};

}

#endif //LABO_SOLVERBODY_H
