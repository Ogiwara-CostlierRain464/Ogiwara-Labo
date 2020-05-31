#include "camera.h"
#include "../math/glm.h"

using glm::mat4;
using glm::perspective;
using glm::radians;
using glm::rotate;
using glm::translate; // Tr

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
  assert(hookedEntity);

  position = {
    hookedEntity->position.x,
    hookedEntity->position.y,
    hookedEntity->position.z
  };

  rotation = hookedEntity->rotation;


}

void labo::render::Camera::hookEntity(const labo::minecraft::Entity *entity) {
  hookedEntity = entity;
}
