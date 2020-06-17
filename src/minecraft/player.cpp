#include "player.h"
#include "level/level.h"
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
  acceleration = {0,0,0};
  box = AABB{spawnPoint, {0.3, 1, 0.3}};

}

void labo::minecraft::Player::update(float deltaTime, Level &level) {
  bool isFlying = false;

  velocity += acceleration;
  acceleration = {0,0,0};

  if(!isFlying){
    if(!isOnGround){
      velocity.y -= 40 * deltaTime;
    }
    isOnGround = false;
  }

  position.x += velocity.x * deltaTime;
  collide(level, {velocity.x, 0, 0}, deltaTime);

  position.y += velocity.y * deltaTime;
  collide(level, {0, velocity.y, 0}, deltaTime);

  position.z += velocity.z * deltaTime;
  collide(level, {0, 0, velocity.z}, deltaTime);

  box.updatePosition(position);
  velocity.x *= 0.95;
  velocity.y *= 0.95;
  velocity.z *= 0.95;

}

void labo::minecraft::Player::collide(
  labo::minecraft::Level &level,
  const glm::vec3 &vel, float deltaTime) {
  for(
    int x = position.x - box.dimensions.x;
    x < position.x + box.dimensions.x;x++
    ){
    for(int y = position.y - box.dimensions.y; y < position.y + 0.7; y++){
      for(int z = position.z - box.dimensions.z;
          z < position.z + box.dimensions.z; z++){
        auto block = level.getBlock(x, y, z);

        if (block.id != Air.id && block.isCollidable) {
          if (vel.y > 0) {
            position.y = y - box.dimensions.y;
            velocity.y = 0;
          }
          else if (vel.y < 0) {
            isOnGround = true;
            position.y = y + box.dimensions.y + 1;
            velocity.y = 0;
          }

          if (vel.x > 0) {
            position.x = x - box.dimensions.x;
          }
          else if (vel.x < 0) {
            position.x = x + box.dimensions.x + 1;
          }

          if (vel.z > 0) {
            position.z = z - box.dimensions.z;
          }
          else if (vel.z < 0) {
            position.z = z + box.dimensions.z + 1;
          }
        }
      }
    }
  }
}
