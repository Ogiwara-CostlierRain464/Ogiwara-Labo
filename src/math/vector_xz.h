#ifndef LABO_VECTOR_XZ_H
#define LABO_VECTOR_XZ_H

#include <SFML/Graphics.hpp>
#include <functional>

namespace labo::math{

struct VectorXZ{
  int x, z;

  bool operator==(const VectorXZ &rhs)const{
    return (x == rhs.x) && (z == rhs.z);
  }
};
}

namespace std{
  template <>
  struct hash<labo::math::VectorXZ>{
    size_t operator()(const labo::math::VectorXZ &vec)const noexcept {
      std::hash<decltype(vec.x)> hasher;

      auto hash1 = hasher(vec.x);
      auto hash2 = hasher(vec.z);

      return std::hash<decltype(vec.x)>{}((hash1 ^ hash2) >> 2);
    }
  };

  template <>
  struct hash<sf::Vector3i>{
    size_t operator()(const sf::Vector3i &vec)const noexcept {
      std::hash<decltype(vec.x)> hasher;

      auto hash1 = hasher(vec.x);
      auto hash2 = hasher(vec.y);
      auto hash3 = hasher(vec.z);

      return std::hash<decltype(vec.x)>{}(hash1 ^ (hash2 << hash3) ^ hash3);
    }
  };
}


#endif //LABO_VECTOR_XZ_H
