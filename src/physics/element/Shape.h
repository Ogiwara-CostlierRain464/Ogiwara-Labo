#ifndef LABO_SHAPE_H
#define LABO_SHAPE_H

#include "ConvexMesh.h"

namespace labo::physics{

struct Shape{
  ConvexMesh geometry;
  glm::vec3 offsetPosition;
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
