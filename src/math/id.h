#ifndef LABO_ID_H
#define LABO_ID_H

#include <functional>

namespace labo::math{
template <typename T>
struct Id{
  size_t value;

  Id(size_t id){
    value = id;
  }

  bool operator==(const Id<T> &id)const{
    return value == id.value;
  }

  bool operator!=(const Id<T> &id)const{
    return value != id.value;
  }
};
}

namespace std{
  template <typename T>
  struct hash<labo::math::Id<T>>{
    size_t operator()(const labo::math::Id<T> &id) const
    {
      std::hash<labo::math::Id<T>> hasher;

      return hasher(id);
    }
  };
}

#endif //LABO_ID_H
