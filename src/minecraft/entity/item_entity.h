#ifndef LABO_ITEM_ENTITY_H
#define LABO_ITEM_ENTITY_H

#include "entity.h"

namespace labo::minecraft{

class ItemEntity: public Entity{
public:
  ItemEntity(
    const math::Id<Entity> &id,
    const glm::vec3 &position)
  : Entity(
    id,
    position,
    {0,0,0},
    {0,0,0},
    physics::AABB{position, {1,1,1}}){}

  void update(float deltaTime, Level *level) override {
    velocity += acceleration;
    acceleration = {0,0,0};

    position += velocity * deltaTime;
  }

private:
  glm::vec3 acceleration = {0,0,0};
};

}

#endif //LABO_ITEM_ENTITY_H
