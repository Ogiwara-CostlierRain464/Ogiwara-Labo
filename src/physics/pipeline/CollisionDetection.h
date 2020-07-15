#ifndef LABO_COLLISIONDETECTION_H
#define LABO_COLLISIONDETECTION_H


#include "../element/State.h"
#include "../element/Collidable.h"
#include "../element/Pair.h"

namespace labo::physics{

void detectionCollision(
  const State *states,
  const Collidable *collidables,
  uint32_t  numRigidBodies,
  const Pair *pairs,
  uint32_t numPairs
);

}

#endif //LABO_COLLISIONDETECTION_H
