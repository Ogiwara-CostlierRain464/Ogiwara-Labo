#include "camera.h"
#include "../math/glm.h"
#include <iostream>

using glm::mat4;
using glm::perspective;
using glm::radians;
using glm::rotate;
using glm::translate; // Tr
using labo::minecraft::Player;

mat4 labo::render::Camera::makeProjectionMat(){
  return perspective(radians(config.fov), config.windowX / config.windowY, 0.1f, 2000.f);
}

mat4 labo::render::Camera::makeViewMat(){
  mat4 m(1.f);

  m = rotate(m, radians(rotation.x), {1,0,0});
  m = rotate(m, radians(rotation.y), {0,1,0});
  m = rotate(m, radians(rotation.z), {0,0,1});

  m = translate(m, -position);

  return m;
}

labo::render::Camera::Camera(CameraConfig conf)
  : config(conf)
{
  projectionMatrix = makeProjectionMat();
}

void labo::render::Camera::update() {
  assert(hookedPlayer);

  position = {
    hookedPlayer->getPosition().x,
    hookedPlayer->getPosition().y + Player::height,
    hookedPlayer->getPosition().z
  };

  rotation = hookedPlayer->getRotation();
  viewMatrix = makeViewMat();
  projViewMatrix = projectionMatrix * viewMatrix;

  frustum.update(projViewMatrix);
}

void labo::render::Camera::hookPlayer(labo::minecraft::Player *player) {
  hookedPlayer = player;
}
