#ifndef LABO_CONSTRAINTSOLVER_H
#define LABO_CONSTRAINTSOLVER_H

#include "../element/State.h"
#include "../element/RigidBoby.h"
#include "../element/Pair.h"
#include "Allocator.h"

namespace labo::physics{

void solveConstrains(
  State *states,
  const RigidBody *bodies,
  uint32_t numRigidBodies,
  const Pair *pairs,
  uint32_t numPairs,
  // Ball Joint
  uint32_t iteration,
  float bias,
  float slop,
  float timeStep,
  Allocator *allocator
);

}

#endif //LABO_CONSTRAINTSOLVER_H
