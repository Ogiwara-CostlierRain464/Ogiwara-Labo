#include "Broadphase.h"
#include "Sort.h"
#include <cmath>

using glm::mat3;
using glm::vec3;
using glm::abs;

constexpr float AABB_EXPAND = 0.01f;

static inline bool intersectAABB(
  const vec3 &centerA,
  const vec3 &halfA,
  const vec3 &centerB,
  const vec3 &halfB
  ){
  if(fabs(centerA[0] - centerB[0]) > halfA[0] + halfB[0]) return false;
  if(fabs(centerA[1] - centerB[1]) > halfA[1] + halfB[1]) return false;
  if(fabs(centerA[2] - centerB[2]) > halfA[2] + halfB[2]) return false;
  return true;
}

void labo::physics::broadPhase(
  const State *states,
  const Collidable *collidables,
  uint32_t numRigidBodies,
  const Pair *oldPairs,
  const uint32_t numOldPairs,
  Pair *newPairs,
  uint32_t &numNewPairs,
  const uint32_t maxPairs,
  Allocator *allocator
){
  assert(states);
  assert(collidables);
  assert(oldPairs);
  assert(newPairs);
  assert(allocator);

  numNewPairs = 0;

  for(size_t i = 0; i < numRigidBodies; i++){
    for(size_t j = i+1; j < numRigidBodies; j++){
      const auto &stateA = states[i];
      const auto &collidableA = collidables[i];
      const auto &stateB = states[j];
      const auto &collidableB = collidables[j];

      mat3 orientationA(stateA.orientation);
      vec3 centerA = stateA.position + orientationA * collidableA.center;
      vec3 halfA = absPerElm(orientationA) * (collidableA.half + vec3(AABB_EXPAND));

      mat3 orientationB(stateB.orientation);
      vec3 centerB = stateB.position + orientationB * collidableB.center;
      vec3 halfB = absPerElm(orientationB) * (collidableB.half + vec3(AABB_EXPAND));

      if(intersectAABB(centerA, halfA, centerB, halfB) && numNewPairs < maxPairs){
        auto &newPair = newPairs[numNewPairs++];

        newPair.rigidBodyA = i<j?i:j;
        newPair.rigidBodyB = i<j?j:i;
        newPair.contact = nullptr;
      }
    }
  }

  assert(newPairs->rigidBodyA < 100 && newPairs->rigidBodyB < 100);

  {
//    auto *sortBuff = (Pair*) allocator->allocate(sizeof(Pair) * numNewPairs);
//    mergeSort<Pair>(newPairs, sortBuff, numNewPairs);
//    allocator->deallocate(sortBuff);
//
    mSort(newPairs, 1, numNewPairs);
  }

  assert(newPairs->rigidBodyA < 100 && newPairs->rigidBodyB < 100);

  Pair *outNewPairs = (Pair*) allocator->allocate(sizeof(Pair) * numNewPairs);
  Pair *outKeepPairs = (Pair*) allocator->allocate(sizeof(Pair) * numOldPairs);
  assert(outNewPairs);
  assert(outKeepPairs);

  uint32_t nNew = 0;
  uint32_t nKeep = 0;
  uint32_t oldId = 0, newId = 0;

  while (oldId < numOldPairs && newId < numNewPairs){
    if(newPairs[newId].key > oldPairs[oldId].key){
      allocator->deallocate(oldPairs[oldId].contact);
      oldId++;
    } else if(newPairs[newId].key == oldPairs[oldId].key){
      assert(nKeep <= numOldPairs);
      outKeepPairs[nKeep] = oldPairs[oldId];
      nKeep++;
      oldId++;
      newId++;
    }else{
      assert(nNew <= numNewPairs);
      outNewPairs[nNew] = newPairs[newId];
      nNew++;
      newId++;
    }
  }

  if(newId < numNewPairs){
    for(; newId < numNewPairs; newId++, nNew++){
      assert(nNew <= numNewPairs);
      outNewPairs[nNew] = newPairs[newId];
    }
  } else if(oldId < numOldPairs){
    for(; oldId < numOldPairs; oldId++){
      allocator->deallocate(oldPairs[oldId].contact);
    }
  }

  for(size_t i =0; i < nNew; i++){
    outNewPairs[i].contact = (Contact*) allocator->allocate(sizeof(Contact));
    outNewPairs[i].contact->reset();
  }

  for(size_t i =0; i < nKeep; i++){
    outKeepPairs[i].contact->refresh(
      states[outKeepPairs[i].rigidBodyA].position,
      states[outKeepPairs[i].rigidBodyA].orientation,
      states[outKeepPairs[i].rigidBodyB].position,
      states[outKeepPairs[i].rigidBodyB].orientation
    );
  }

  numNewPairs = 0;
  for(size_t i =0; i < nKeep; i++){
    outKeepPairs[i].type = Keep;
    newPairs[numNewPairs++] = outKeepPairs[i];
  }
  for(size_t i=0; i < nNew; i++){
    outNewPairs[i].type = New;
    newPairs[numNewPairs++] = outNewPairs[i];
  }

  allocator->deallocate(outKeepPairs);
  allocator->deallocate(outNewPairs);

  {
//    Pair *sortBuff = (Pair*) allocator->allocate(sizeof(Pair) * numNewPairs);
//    mergeSort<Pair>(newPairs, sortBuff, numNewPairs);
//    allocator->deallocate(sortBuff);

    mSort(newPairs, 1, numNewPairs);
  }
}