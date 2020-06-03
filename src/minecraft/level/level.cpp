#include "level.h"

using glm::vec3;

labo::minecraft::Level::Level():
  player(Player({1,1,1}))
{

}

void labo::minecraft::Level::update(float deltaTime) {
  player.update(deltaTime);

  for(auto &event: events){
    event->handle(*this);
  }
  events.clear();

}
