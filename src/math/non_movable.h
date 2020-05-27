#ifndef LABO_NON_MOVABLE_H
#define LABO_NON_MOVABLE_H

namespace labo::math{

/**
 * Moveできないようにする
 */
struct NonMovable{
  NonMovable() = default;
  NonMovable(NonMovable&&) = delete;
  NonMovable &operator=(NonMovable &&) = delete;
};


}

#endif //LABO_NON_MOVABLE_H
