#ifndef LABO_ENTITY_H
#define LABO_ENTITY_H

#include "../../math/glm.h"
#include "../../math/non_copyable.h"
#include "../../physics/aabb.h"
#include "../../math/id.h"

namespace labo::minecraft{

struct Entity: public labo::math::NonCopyable{
  math::Id<Entity> id;
  glm::vec3 position;
  // オイラー角の姿勢
  // pitch, yaw, roll
  glm::vec3 rotation;
  // 速度
  glm::vec3 velocity;
  labo::physics::AABB box;

  Entity(
    const math::Id<Entity> &id,
    const glm::vec3 &position,
    const glm::vec3 &rotation,
    const glm::vec3 &velocity,
    const physics::AABB &box)
  : id(id)
  , position(position)
  , rotation(rotation)
  , velocity(velocity)
  , box(box) {}

};

}

#endif //LABO_ENTITY_H
