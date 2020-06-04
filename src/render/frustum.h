#ifndef LABO_FRUSTUM_H
#define LABO_FRUSTUM_H

#include "../math/glm.h"
#include "../physics/aabb.h"
#include <array>

namespace labo::render{

struct Plane{
  // 法線
  glm::vec3 normal;
  // 原点からの距離
  float distanceToOrigin;

  /**
   * pointのこの平面からの距離
   */
  [[nodiscard]]
  float distanceToPoint(const glm::vec3 &point) const;
};

/**
 * 視錐台
 * The view frustum is the region of space
 * in the modeled world that may appear on the screen.
 */
class ViewFrustum{
public:
  void update(const glm::mat4 & projViewMatrix) noexcept;

  bool isBoxInFrustum(const labo::physics::AABB &box);

private:
  std::array<Plane, 6> planes;
};

}
#endif //LABO_FRUSTUM_H
