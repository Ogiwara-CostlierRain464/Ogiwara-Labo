#ifndef LABO_INTEGRATE_H
#define LABO_INTEGRATE_H

#include "../element/State.h"
#include "../element/RigidBoby.h"
#include "../../math/glm.h"

namespace labo::physics{


// 外力を与える
void applyExternalForce(
  State &state,
  const RigidBody &body,
  const glm::vec3 &externalForce,
  const glm::vec3 &externalTorque,
  float timeStep
);

// 統合
void integrate(
  State *states,
  uint32_t numRigidBodies,
  float timeStep
);

}


#endif //LABO_INTEGRATE_H
