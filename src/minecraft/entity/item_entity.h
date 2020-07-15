#ifndef LABO_ITEM_ENTITY_H
#define LABO_ITEM_ENTITY_H

#include "entity.h"

namespace labo::minecraft{

class ItemEntity: public Entity{
public:
  ItemEntity(
    const math::Id<Entity> &id,
    const glm::vec3 &position,
    const glm::vec3 &rotation = {0,0,0},
    const glm::vec3 &velocity = {0,0,0})
  : Entity(
    id,
    position,
    rotation,
    velocity,
    physics::AABB{position, {1,1,1}}){}

  void update(float deltaTime, Level &level) override {
    //position += velocity * deltaTime;
    //rotation += velocity * deltaTime;
  }

private:
  glm::vec3 acceleration = {0,0,0};
};

}

#endif //LABO_ITEM_ENTITY_H
