#ifndef LABO_RIGIDBOBY_H
#define LABO_RIGIDBOBY_H

#include "../../math/glm.h"

namespace labo::physics{

struct RigidBody{
  // 慣性テンソル
  glm::mat3 inertia;
  // 質量
  float mass;
  // 反発係数
  float restitution;
  // 摩擦係数
  float friction;

  void reset(){
    inertia = glm::mat3(1.0);
    mass = 1;
    restitution = 0.2f;
    friction = 0.6f;
  }
};

}


#endif //LABO_RIGIDBOBY_H
