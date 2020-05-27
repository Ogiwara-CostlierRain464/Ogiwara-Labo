#ifndef LABO_NON_COPYABLE_H
#define LABO_NON_COPYABLE_H

namespace labo::math{

/**
 * コピーできないようにする
 */
struct NonCopyable{
  NonCopyable() = default;
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable &operator=(const NonCopyable&) = delete;
};

}

#endif //LABO_NON_COPYABLE_H
