#include "CollisionDetection.h"
#include "../collision/convex_convex_contact.h"

using glm::vec3;
using glm::mat3;

void labo::physics::detectionCollision(
  const State *states,
  const Collidable *collidables,
  uint32_t numRigidBodies,
  const Pair *pairs,
  uint32_t numPairs
){
  assert(states);
  assert(collidables);
  assert(pairs);

  for(size_t i = 0; i < numPairs; i++){
    const Pair &pair = pairs[i];

    assert(pair.contact);

    const State &stateA = states[pair.rigidBodyA];
    const State &stateB = states[pair.rigidBodyB];
    const Collidable &collA = collidables[pair.rigidBodyA];
    const Collidable &collB = collidables[pair.rigidBodyB];

    auto transformA = math::Transform3::from(stateA.orientation, stateA.position);
    auto transformB = math::Transform3::from(stateB.orientation, stateB.position);

    for(size_t j = 0; j < collA.numShapes; j++){
      const Shape &shapeA = collA.shapes[j];
      auto offsetTransformA = math::Transform3::from(shapeA.offsetOrientation, shapeA.offsetPosition);
      // shapeAをworld座標に変換 P206 (7)
      auto worldTransformA = transformA * offsetTransformA;

      for(size_t k=0; k < collB.numShapes; k++){
        const Shape &shapeB = collB.shapes[k];
        auto offsetTransformB = math::Transform3::from(shapeB.offsetOrientation, shapeB.offsetPosition);
        // shapeBをworld座標に変換 P206 (7)
        auto worldTransformB = transformB * offsetTransformB;

        vec3 contactPointA;
        vec3 contactPointB;
        vec3 normal;
        float penetrationDepth;

        if(convexConvexContact(
          shapeA.geometry, worldTransformA,
          shapeB.geometry, worldTransformB,
          normal, penetrationDepth,
          contactPointA, contactPointB
          ) && penetrationDepth < 0.f){

          // 衝突点を剛体の座標系へ変換し、コンタクトへ追加
          pair.contact->addContact(
            penetrationDepth, normal,
            offsetTransformA.getTranslation() + offsetTransformA.getUpper3x3() * contactPointA,
            offsetTransformB.getTranslation() + offsetTransformB.getUpper3x3() * contactPointB
            );
        }
      }
    }
  }
}