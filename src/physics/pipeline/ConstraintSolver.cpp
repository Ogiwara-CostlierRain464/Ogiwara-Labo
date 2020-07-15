#include "ConstraintSolver.h"
#include "../element/SolverBody.h"
#include "../collision/vector_function.h"
#include <cassert>
#include <cmath>
#include "../base.h"

using glm::vec3;
using glm::mat3;
using glm::inverse;
using glm::transpose;
using glm::rotate;
using glm::cross;
using glm::dot;
using std::min;

void labo::physics::solveConstrains(
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
){
  assert(states);
  assert(bodies);
  assert(pairs);

  auto *solverBodies = (SolverBody*) allocator->allocate(sizeof(SolverBody) * numRigidBodies);
  assert(solverBodies);

  for(size_t i = 0; i < numRigidBodies; i++){
    auto &state = states[i];
    const auto &body = bodies[i];
    auto &solverBody = solverBodies[i];

    solverBody.orientation = state.orientation;
    solverBody.deltaLinearVelocity = vec3(0.f);
    solverBody.deltaAngularVelocity = vec3(0.f);

    if(state.motionType == MotionType::Static){
      solverBody.massInv = 0.f;
      solverBody.inertiaInv = mat3(0.f);
    }else {
      solverBody.massInv = 1.f / body.mass;
      mat3 m(solverBody.orientation);
      solverBody.inertiaInv = m * inverse(body.inertia) * transpose(m);
    }
  }

  for(size_t i=0; i < numPairs; i++){
    const auto &pair = pairs[i];
    auto &stateA = states[pair.rigidBodyA];
    const auto &bodyA = bodies[pair.rigidBodyA];
    auto &solverBodyA = solverBodies[pair.rigidBodyA];

    auto &stateB = states[pair.rigidBodyB];
    const auto &bodyB = bodies[pair.rigidBodyB];
    auto &solverBodyB = solverBodies[pair.rigidBodyB];

    assert(pair.contact);

    pair.contact->friction = sqrtf(bodyA.friction * bodyB.friction);

    for(int j=0; j < pair.contact->numContacts; j++) {
      auto &cp = pair.contact->contactPoints[j];

      auto rA = rotate(solverBodyA.orientation, cp.pointA);
      auto rB = rotate(solverBodyB.orientation, cp.pointB);

      mat3 K = mat3(1) * (solverBodyA.massInv + solverBodyB.massInv) -
               crossMatrix(rA) * solverBodyA.inertiaInv * crossMatrix(rA) -
               crossMatrix(rB) * solverBodyB.inertiaInv * crossMatrix(rB);

      vec3 velocityA = stateA.linearVelocity + cross(stateA.angularVelocity, rA);
      vec3 velocityB = stateB.linearVelocity + cross(stateB.angularVelocity, rB);
      vec3 relativeVelocity = velocityA - velocityB;

      vec3 tangent1, tangent2;

      calcTangentVector(cp.normal, tangent1, tangent2);

      float restitution = pair.type == New ? 0.5f * (bodyA.restitution + bodyB.restitution) : 0.0f;

      // 反発方向法線
      {
        vec3 axis = cp.normal;
        float denominator = dot(K * axis, axis);
        cp.constraints[0].jacDiagInv = 1.f / denominator;
        cp.constraints[0].rhs = -(1.f + restitution) * dot(relativeVelocity, axis);
        cp.constraints[0].rhs -= (bias * min(0.f, cp.distance + slop)) / timeStep;
        cp.constraints[0].rhs *= cp.constraints[0].jacDiagInv;
        cp.constraints[0].lowerLimit = 0.f;
        cp.constraints[0].upperLimit = std::numeric_limits<float>::max();
        cp.constraints[0].axis = axis;
      }

      // 摩擦1
      {
        vec3 axis = tangent1;
        float denominator = dot(K * axis, axis);
        cp.constraints[1].jacDiagInv = 1.f / denominator;
        cp.constraints[1].rhs = -dot(relativeVelocity,axis);
        cp.constraints[1].rhs *= cp.constraints[1].jacDiagInv;
        cp.constraints[1].lowerLimit = 0.f;
        cp.constraints[1].upperLimit = 0.f;
        cp.constraints[1].axis = axis;
      }

      // 摩擦2
      {
        vec3 axis = tangent2;
        float denominator = dot(K * axis, axis);
        cp.constraints[2].jacDiagInv = 1.f / denominator;
        cp.constraints[2].rhs = -dot(relativeVelocity,axis);
        cp.constraints[2].rhs *= cp.constraints[2].jacDiagInv;
        cp.constraints[2].lowerLimit = 0.f;
        cp.constraints[2].upperLimit = 0.f;
        cp.constraints[2].axis = axis;
      }
    }
  }

  // Warm starting (optional)
  for(size_t i=0;i<numPairs;i++) {
    const Pair &pair = pairs[i];

    SolverBody &solverBodyA = solverBodies[pair.rigidBodyA];
    SolverBody &solverBodyB = solverBodies[pair.rigidBodyB];

    for(size_t j=0;j<pair.contact->numContacts;j++) {
      ContactPoint &cp = pair.contact->contactPoints[j];
      vec3 rA = rotate(solverBodyA.orientation,cp.pointA);
      vec3 rB = rotate(solverBodyB.orientation,cp.pointB);

      for(size_t k=0;k<3;k++) {
        float deltaImpulse = cp.constraints[k].accumImpulse;
        solverBodyA.deltaLinearVelocity += deltaImpulse * solverBodyA.massInv * cp.constraints[k].axis;
        solverBodyA.deltaAngularVelocity += deltaImpulse * solverBodyA.inertiaInv * cross(rA,cp.constraints[k].axis);
        solverBodyB.deltaLinearVelocity -= deltaImpulse * solverBodyB.massInv * cp.constraints[k].axis;
        solverBodyB.deltaAngularVelocity -= deltaImpulse * solverBodyB.inertiaInv * cross(rB,cp.constraints[k].axis);
      }
    }
  }

  // 拘束の反復計算
  for(size_t itr=0; itr < iteration ; itr++){
     for(size_t i=0; i < numPairs; i++){
       const auto &pair = pairs[i];

       auto &solverBodyA = solverBodies[pair.rigidBodyA];
       auto &solverBodyB = solverBodies[pair.rigidBodyB];

       for(size_t j=0; j < pair.contact->numContacts; j++){
         auto &cp = pair.contact->contactPoints[j];
         auto rA = rotate(solverBodyA.orientation, cp.pointA);
         auto rB = rotate(solverBodyB.orientation, cp.pointB);

         // 反発方向
         {
           auto &constraint = cp.constraints[0];
           float deltaImpulse = constraint.rhs;
           vec3 deltaVelocityA = solverBodyA.deltaLinearVelocity + cross(solverBodyA.deltaAngularVelocity, rA);
           vec3 deltaVelocityB = solverBodyB.deltaLinearVelocity + cross(solverBodyB.deltaAngularVelocity, rB);
           deltaImpulse -= constraint.jacDiagInv * dot(constraint.axis, deltaVelocityA - deltaVelocityB);
           float oldImpulse = constraint.accumImpulse;
           constraint.accumImpulse = clamp(oldImpulse + deltaImpulse, constraint.lowerLimit, constraint.upperLimit);
           deltaImpulse = constraint.accumImpulse - oldImpulse;
           solverBodyA.deltaLinearVelocity += deltaImpulse * solverBodyA.massInv * constraint.axis;
           solverBodyA.deltaAngularVelocity += deltaImpulse * solverBodyA.inertiaInv * cross(rA, constraint.axis);
           solverBodyB.deltaLinearVelocity -= deltaImpulse * solverBodyB.massInv * constraint.axis;
           solverBodyB.deltaAngularVelocity -= deltaImpulse * solverBodyB.inertiaInv * cross(rB, constraint.axis);
         }

         float maxFriction = pair.contact->friction * abs(cp.constraints[0].accumImpulse);
         cp.constraints[1].lowerLimit = -maxFriction;
         cp.constraints[1].upperLimit = maxFriction;
         cp.constraints[2].lowerLimit = -maxFriction;
         cp.constraints[2].upperLimit = maxFriction;

         // 摩擦1
         {
           auto &constraint = cp.constraints[1];
           float deltaImpulse = constraint.rhs;
           vec3 deltaVelocityA = solverBodyA.deltaLinearVelocity + cross(solverBodyA.deltaAngularVelocity, rA);
           vec3 deltaVelocityB = solverBodyB.deltaLinearVelocity + cross(solverBodyB.deltaAngularVelocity, rB);
           deltaImpulse -= constraint.jacDiagInv * dot(constraint.axis, deltaVelocityA - deltaVelocityB);
           float oldImpulse = constraint.accumImpulse;
           constraint.accumImpulse = clamp(oldImpulse + deltaImpulse, constraint.lowerLimit, constraint.upperLimit);
           deltaImpulse = constraint.accumImpulse - oldImpulse;
           solverBodyA.deltaLinearVelocity += deltaImpulse * solverBodyA.massInv * constraint.axis;
           solverBodyA.deltaAngularVelocity += deltaImpulse * solverBodyA.inertiaInv * cross(rA, constraint.axis);
           solverBodyB.deltaLinearVelocity -= deltaImpulse * solverBodyB.massInv * constraint.axis;
           solverBodyB.deltaAngularVelocity -= deltaImpulse * solverBodyB.inertiaInv * cross(rB, constraint.axis);
         }

         // 摩擦2
         {
           auto &constraint = cp.constraints[2];
           float deltaImpulse = constraint.rhs;
           vec3 deltaVelocityA = solverBodyA.deltaLinearVelocity + cross(solverBodyA.deltaAngularVelocity, rA);
           vec3 deltaVelocityB = solverBodyB.deltaLinearVelocity + cross(solverBodyB.deltaAngularVelocity, rB);
           deltaImpulse -= constraint.jacDiagInv * dot(constraint.axis, deltaVelocityA - deltaVelocityB);
           float oldImpulse = constraint.accumImpulse;
           constraint.accumImpulse = clamp(oldImpulse + deltaImpulse, constraint.lowerLimit, constraint.upperLimit);
           deltaImpulse = constraint.accumImpulse - oldImpulse;
           solverBodyA.deltaLinearVelocity += deltaImpulse * solverBodyA.massInv * constraint.axis;
           solverBodyA.deltaAngularVelocity += deltaImpulse * solverBodyA.inertiaInv * cross(rA, constraint.axis);
           solverBodyB.deltaLinearVelocity -= deltaImpulse * solverBodyB.massInv * constraint.axis;
           solverBodyB.deltaAngularVelocity -= deltaImpulse * solverBodyB.inertiaInv * cross(rB, constraint.axis);
         }
       }
     }
  }

  for(size_t i=0; i < numRigidBodies; i++){
    states[i].linearVelocity += solverBodies[i].deltaLinearVelocity;
    states[i].angularVelocity += solverBodies[i].deltaAngularVelocity;
  }

  allocator->deallocate(solverBodies);
}