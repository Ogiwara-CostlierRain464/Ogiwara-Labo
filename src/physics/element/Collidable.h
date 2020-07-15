#ifndef LABO_COLLIDABLE_H
#define LABO_COLLIDABLE_H

#include <cstdint>
#include <array>
#include <limits>
#include "Shape.h"

namespace {
  constexpr int NUM_SHAPES = 5;
}

namespace labo::physics{

// 形状コンテナ
struct Collidable{
  uint8_t numShapes;
  std::array<Shape, NUM_SHAPES> shapes;
  glm::vec3 center;
  glm::vec3 half;

  void reset(){
    numShapes = 0;
    center = glm::vec3(0.f);
    half = glm::vec3(0.f);
  }

  // 形状の登録
  // 空きがなければ無視
  void addShape(const Shape &shape){
    if(numShapes < NUM_SHAPES){
      shapes[numShapes++] = shape;
    }
  }

  // 形状登録の完了を通知する
  void finish(){
    glm::vec3 AABBMax(-std::numeric_limits<float>::max());
    glm::vec3 AABBMin(std::numeric_limits<float>::max());

    for(size_t i = 0; i < numShapes; i++){
      const ConvexMesh &mesh = shapes[i].geometry;

      for(size_t v = 0; v < mesh.numVertices ; v++){
        AABBMax = maxPerElem(
          AABBMax,
          shapes[i].offsetPosition +
          glm::rotate(
            shapes[i].offsetOrientation,
            mesh.vertices[v]));

        AABBMin = minPerElem(
          AABBMin,
          shapes[i].offsetPosition +
          glm::rotate(
            shapes[i].offsetOrientation,
            mesh.vertices[v]));
      }

      center = (AABBMax + AABBMin) * 0.5f;
      half = (AABBMax - AABBMin) * 0.5f;
    }
  }
};

}

#endif //LABO_COLLIDABLE_H
