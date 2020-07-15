#ifndef LABO_CONSTRAIN_H
#define LABO_CONSTRAIN_H

#include "../../math/glm.h"

namespace labo::physics{


struct Constraint{
  // 拘束軸
  glm::vec3 axis;
  // 拘束式の分母
  float jacDiagInv;
  // 初期拘束力
  float rhs;
  // 拘束力の下限
  float lowerLimit;
  // 拘束力の上限
  float upperLimit;
  // 蓄積される拘束力
  float accumImpulse;
};

}

#endif //LABO_CONSTRAIN_H
