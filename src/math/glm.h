#ifndef LABO_GLM_H
#define LABO_GLM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace glm{

inline const glm::vec3 maxPerElem(const glm::vec3 &vec0, const glm::vec3 &vec1){
  float x = glm::max(vec0[0], vec1[0]);
  float y = glm::max(vec0[1], vec1[1]);
  float z = glm::max(vec0[2], vec1[2]);

  return glm::vec3(x, y, z);
}

inline const glm::vec3 minPerElem(const glm::vec3 &vec0, const glm::vec3 &vec1){
  float x = glm::min(vec0[0], vec1[0]);
  float y = glm::min(vec0[1], vec1[1]);
  float z = glm::min(vec0[2], vec1[2]);

  return glm::vec3(x, y, z);
}

inline const glm::mat3 absPerElm(const glm::mat3 &mat){
  auto x = glm::abs(mat[0]);
  auto y = glm::abs(mat[1]);
  auto z = glm::abs(mat[2]);

  return glm::mat3(x, y, z);
}

// mul two 3D vectors per elem
inline const glm::vec3 mulPerElem(const glm::vec3 &vec0, const glm::vec3 &vec1){
  return glm::vec3(
    vec0[0] * vec1[0],
    vec0[1] * vec1[1],
    vec0[2] * vec1[2]
  );
}

// cf. P237
inline const glm::mat3 crossMatrix(const glm::vec3 &vec){
  return glm::mat3(
    glm::vec3(0, -vec[2], vec[1]),
    glm::vec3(vec[2], 0, -vec[0]),
    glm::vec3(-vec[1], vec[0], 0)
  );
}

}


namespace labo::math{


struct Transform3{
  glm::mat3 orientation;
  glm::vec3 position;

  Transform3 inverse()const{
    auto transR = glm::transpose(orientation);
    return Transform3::from(transR, - transR * position);
  }

  glm::mat3 getUpper3x3()const{
    return orientation;
  }

  glm::vec3 getTranslation()const{
    return position;
  }

  Transform3 &&operator*(const Transform3 &rhs)const{
    glm::mat4 lhs = this->toMat4();
    glm::mat4 rhs_ = rhs.toMat4();

    return Transform3::from(lhs * rhs_);
  }

  glm::mat4 &&toMat4()const{
    return std::move(glm::mat4(
      glm::vec4(orientation[0], position[0]),
      glm::vec4(orientation[1], position[1]),
      glm::vec4(orientation[2], position[2]),
      glm::vec4(0,0,0, 1)
    ));
  }

  static Transform3 &&from(const glm::mat4 &mat4){
    glm::vec4 col0 = mat4[0];
    glm::vec4 col1 = mat4[1];
    glm::vec4 col2 = mat4[2];
    glm::vec4 col3 = mat4[0];

    return std::move(Transform3{
      glm::mat3(
        glm::vec3(col0[0], col0[1], col0[2]),
        glm::vec3(col1[0], col1[1], col1[2]),
        glm::vec3(col2[0], col2[1], col2[2])
      ),
      glm::vec3(col0[3], col1[3], col2[3])
    });
  }

  static Transform3 &&from(const glm::mat3 &rotate, const glm::vec3 move){
    return std::move(Transform3{
      rotate,
      move
    });
  }

  static Transform3 &&from(const glm::quat &rotate, const glm::vec3 move){
    return Transform3::from(glm::mat3(rotate), move);
  }

};

}

#endif //LABO_GLM_H
