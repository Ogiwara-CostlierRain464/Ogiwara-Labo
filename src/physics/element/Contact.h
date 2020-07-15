#ifndef LABO_CONTACT_H
#define LABO_CONTACT_H

#include <cstdint>
#include <array>
#include "../../math/glm.h"
#include "Constraint.h"

namespace {
  constexpr int NUM_CONTACTS = 4;
}

namespace labo::physics{

struct ContactPoint{
  // 貫通深度
  float distance;
  // 衝突点（剛体Aのローカル座標系）
  glm::vec3 pointA;
  // 衝突点（剛体Bのローカル座標系）
  glm::vec3 pointB;
  // 衝突点の法線ベクトル（ワールド座標系）
  glm::vec3 normal;
  std::array<Constraint,3> constraints;

  void reset(){
    constraints[0].accumImpulse = 0.f;
    constraints[1].accumImpulse = 0.f;
    constraints[2].accumImpulse = 0.f;
  }
};

struct Contact{
  // 衝突の数
  uint32_t numContacts;
  // 摩擦
  float friction;
  std::array<ContactPoint, NUM_CONTACTS> contactPoints;

  // 同一衝突点を探索する
  int findNearestContactPoint(
    const glm::vec3 &newPointA,
    const glm::vec3 &newPointB,
    const glm::vec3 &newNormal
  );

  // 衝突点を入れ替える
  int sort4ContactPoints(
    const glm::vec3 &newPoint,
    float newDistance
  );

  // 衝突点を破棄する
  void removeContactPoint(int i);

  void reset();

  // 衝突点をリフレッシュする
  void refresh(
    const glm::vec3 &pA,
    const glm::quat &qA,
    const glm::vec3 &pB,
    const glm::quat &qB
  );

  // 衝突点をマージ
  void merge(const Contact &contact);

  // 衝突点を追加する
  void addContact(
    float penetrationDepth,
    const glm::vec3 &normal,
    const glm::vec3 &contactPointA,
    const glm::vec3 &contactPointB
  );
};

}

#endif //LABO_CONTACT_H
