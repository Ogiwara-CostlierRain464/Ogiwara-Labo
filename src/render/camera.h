#ifndef LABO_CAMERA_H
#define LABO_CAMERA_H

#include "../minecraft/entity/entity.h"

namespace labo::render{

struct CameraConfig{
  float windowX;
  float windowY;
  float fov;
};

class Camera{
public:
  explicit Camera(CameraConfig conf);

  void update();
  void hookEntity(const labo::minecraft::Entity *entity);

  [[nodiscard]]
  const glm::mat4 &getViewMatrix() const noexcept{
    return viewMatrix;
  }

  [[nodiscard]]
  const glm::mat4 &getProjMatrix() const noexcept{
    return projectionMatrix;
  }

  [[nodiscard]]
  const glm::mat4 &getProjectionViewMatrix() const noexcept{
    return projViewMatrix;
  }

private:
  glm::mat4 makeProjectionMat();
  glm::mat4 makeViewMat();

  const labo::minecraft::Entity *hookedEntity;
  glm::vec3 position;
  // オイラー角
  glm::vec3 rotation;

  CameraConfig config;
  glm::mat4 projectionMatrix;
  glm::mat4 viewMatrix;
  glm::mat4 projViewMatrix;
};
}

#endif //LABO_CAMERA_H
