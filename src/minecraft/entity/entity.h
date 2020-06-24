#ifndef LABO_ENTITY_H
#define LABO_ENTITY_H

#include "../../math/glm.h"
#include "../../math/non_copyable.h"
#include "../../physics/aabb.h"

namespace labo::minecraft{

struct Entity: public labo::math::NonCopyable{
  glm::vec3 position;
  // オイラー角の姿勢
  // pitch, yaw, roll
  glm::vec3 rotation;
  // 速度
  glm::vec3 velocity;
  labo::physics::AABB box;
};

}

#endif //LABO_ENTITY_H
