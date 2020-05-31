#ifndef LABO_PLAYER_H
#define LABO_PLAYER_H

#include "entity/entity.h"

namespace labo::minecraft{

class Player: public Entity{
public:
  static constexpr float height = 0.7;

  explicit Player(glm::vec3 spawnPoint);
  void update(float deltaTime);

  glm::vec3 acceleration;

};

}


#endif //LABO_PLAYER_H
