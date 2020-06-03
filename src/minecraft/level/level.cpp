#include "level.h"

using glm::vec3;

labo::minecraft::Level::Level():
  player(Player({1,1,1}))
{

}


labo::minecraft::Block labo::minecraft::Level::getBlock(int x, int y, int z) {
  return labo::minecraft::Block();
}

void labo::minecraft::Level::setBlock(int x, int y, int z, labo::minecraft::Block block) {

}

void labo::minecraft::Level::update(float deltaTime) {
  player.update(deltaTime);

  for(auto &event: events){
    event->handle(*this);
  }
  events.clear();

}
