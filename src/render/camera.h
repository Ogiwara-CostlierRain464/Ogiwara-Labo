#ifndef LABO_CAMERA_H
#define LABO_CAMERA_H

#include "../minecraft/entity/entity.h"
#include "../minecraft/player.h"
#include "frustum.h"

namespace labo::render{

struct CameraConfig{
  float windowX;
  float windowY;
  float fov;
};

class Camera: public labo::math::NonCopyable{
public:
  explicit Camera(CameraConfig conf);

  void update();
  void hookPlayer(labo::minecraft::Player *player);

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

  [[nodiscard]]
  glm::vec3 getPosition()const{
    return position;
  }

  [[nodiscard]]
  const ViewFrustum &getFrustum() const noexcept {
    return frustum;
  }

private:
  glm::mat4 makeProjectionMat();
  glm::mat4 makeViewMat();

  minecraft::Player *hookedPlayer = nullptr;
  glm::vec3 position;
  // オイラー角
  glm::vec3 rotation;

  CameraConfig config;
  ViewFrustum frustum;

  // Buffer
  glm::mat4 projectionMatrix;
  glm::mat4 viewMatrix;
  glm::mat4 projViewMatrix;
};
}

#endif //LABO_CAMERA_H
