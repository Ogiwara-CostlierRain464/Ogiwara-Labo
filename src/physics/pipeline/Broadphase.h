#ifndef LABO_BROADPHASE_H
#define LABO_BROADPHASE_H

#include "../element/State.h"
#include "../element/Collidable.h"
#include "../element/Pair.h"
#include "Allocator.h"

namespace labo::physics{

void broadPhase(
  const State *states,
  const Collidable *collidables,
  uint32_t numRigidBodies,
  const Pair *oldPairs,
  const uint32_t numOldPairs,
  Pair *newPairs,
  uint32_t &numNewPairs,
  const uint32_t maxPairs,
  Allocator *allocator
);
}


#endif //LABO_BROADPHASE_H
