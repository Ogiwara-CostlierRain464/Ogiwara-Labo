#include "Integrate.h"

using glm::mat3;
using glm::vec3;
using glm::transpose;
using glm::inverse;
using glm::length;
using glm::quat;

// 外力を与える
void labo::physics::applyExternalForce(
  State &state,
  const RigidBody &body,
  const glm::vec3 &externalForce,
  const glm::vec3 &externalTorque,
  float timeStep
){
  if(state.motionType == MotionType::Static){
    return;
  }

  mat3 orientation(state.orientation);
  mat3 worldInertia = orientation * body.inertia * transpose(orientation);
  mat3 worldInertiaInv = orientation * inverse(body.inertia) * transpose(orientation);
  vec3 angularMomentum = worldInertia * state.angularVelocity;

  state.linearVelocity += externalForce / body.mass * timeStep;
  angularMomentum += externalTorque * timeStep;
  state.angularVelocity = worldInertiaInv * angularMomentum;

  float linVelSqr = length(state.linearVelocity);
  if(linVelSqr > MAX_LINEAR_VELOCITY * MAX_LINEAR_VELOCITY){
    state.linearVelocity = (state.linearVelocity/sqrtf(linVelSqr)) * MAX_LINEAR_VELOCITY;
  }

  float angVelSqr = length(state.angularVelocity);
  if(angVelSqr > (MAX_ANGULAR_VELOCITY * MAX_ANGULAR_VELOCITY)){
    state.angularVelocity = (state.angularVelocity/sqrtf(angVelSqr)) * MAX_ANGULAR_VELOCITY;
  }
}

// 統合
void labo::physics::integrate(
  State *states,
  uint32_t numRigidBodies,
  float timeStep
){
  for(size_t i=0; i<numRigidBodies;i++){
    auto &state = states[i];
    quat dAng = quat(state.angularVelocity) * state.orientation * 0.5f;

    state.position += state.linearVelocity * timeStep;
    state.orientation = glm::normalize(state.orientation + dAng * timeStep);
  }
}