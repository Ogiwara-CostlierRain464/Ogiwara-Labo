#ifndef LABO_RAY_H
#define LABO_RAY_H

#include "glm.h"

namespace labo::math{

/**
 * プレイヤーの視点の先を表す
 */
class Ray{
public:
  Ray(const glm::vec3 &position,
    const glm::vec3 &direction)
  : rayStart(position)
  , rayEnd(position)
  , direction(direction)
  {}

  void step(float scale){
    float yaw = glm::radians(direction.y + 90);
    float pitch = glm::radians(direction.x);

    auto &p = rayEnd;
    p.x -= glm::cos(yaw) * scale;
    p.z -= glm::sin(yaw) * scale;
    p.y -= glm::tan(pitch) * scale;
  }

  const glm::vec3 &getEnd()const{
    return rayEnd;
  }

  float getLength()const{
    return glm::distance(rayStart, rayEnd);
  }

private:
  glm::vec3 rayStart;
  glm::vec3 rayEnd;
  glm::vec3 direction;
};

}

#endif //LABO_RAY_H
