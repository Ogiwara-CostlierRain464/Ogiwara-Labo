#ifndef LABO_STATE_H
#define LABO_STATE_H

#include "../../math/glm.h"

namespace labo::physics {

constexpr float MAX_LINEAR_VELOCITY = 340.f;
constexpr float MAX_ANGULAR_VELOCITY = (3.14 * 60.f);

enum MotionType {
  Active,
  Static
};

struct State {
  glm::vec3 position;
  // 姿勢
  glm::quat orientation;
  // 並進速度
  glm::vec3 linearVelocity;
  // 回転速度
  glm::vec3 angularVelocity;
  MotionType motionType;

  void reset() {
    position = glm::vec3(0.f);
    orientation = glm::quat();
    linearVelocity = glm::vec3(0.f);
    angularVelocity = glm::vec3(0.f);
    motionType = MotionType::Active;
  }
};

}


#endif //LABO_STATE_H
