#include "player.h"
#include "../physics/aabb.h"
#include <iostream>

using glm::vec3;
using labo::physics::AABB;

labo::minecraft::Player::Player(vec3 spawnPoint)
  : Entity{}
{
  position = spawnPoint;
  rotation = {0,0,0};
  velocity = {0,0,0};
  box = AABB{spawnPoint, {0.3, 1, 0.3}};

}

void labo::minecraft::Player::update(float deltaTime) {
  velocity += acceleration;
  acceleration = {0,0,0};

  position.x += velocity.x * deltaTime;
  position.y += velocity.y * deltaTime;
  position.z += velocity.z * deltaTime;


  box.updatePosition(position);
  velocity.x *= 0.95;
  velocity.y *= 0.95;
  velocity.z *= 0.95;

}
