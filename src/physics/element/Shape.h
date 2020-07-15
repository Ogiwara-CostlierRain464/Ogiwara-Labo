#ifndef LABO_SHAPE_H
#define LABO_SHAPE_H

#include "ConvexMesh.h"

namespace labo::physics{

struct Shape{
  // 凸メッシュ
  ConvexMesh geometry;
  // オフセットの位置
  glm::vec3 offsetPosition;
  // オフセットの姿勢
  glm::quat offsetOrientation;
  void *userData;

  void reset(){
    geometry.reset();
    offsetPosition = glm::vec3(0.f);
    offsetOrientation = glm::quat();
    userData = nullptr;
  }
};
}

#endif //LABO_SHAPE_H
