#ifndef LABO_PLAYER_H
#define LABO_PLAYER_H

#include "entity/entity.h"

namespace labo::minecraft{

class Level;

class Player: public Entity{
public:
  static constexpr float height = 0.7;

  explicit Player(glm::vec3 spawnPoint);
  void update(float deltaTime, Level &level);
  void collide(Level &level, const glm::vec3 &vel, float deltaTime);

  glm::vec3 acceleration{0};


  bool isFlying(){
    return flying;
  }

  void toggleFlying(){
    flying = !flying;
  }

  bool isOnGround(){
    return onGround;
  }

  void setOnGround(bool onGround_){
    onGround = onGround_;
  }

private:
  bool flying = true;
  bool onGround = false;
};

}


#endif //LABO_PLAYER_H
