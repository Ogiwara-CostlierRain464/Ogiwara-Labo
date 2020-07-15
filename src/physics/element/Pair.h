#ifndef LABO_PAIR_H
#define LABO_PAIR_H

#include <cstdint>
#include "Contact.h"

namespace labo::physics{

enum PairType{
  New, Keep
};

struct Pair{
  PairType type;
  union {
    uint64_t key;
    struct {
      uint32_t rigidBodyA;
      uint32_t rigidBodyB;
    };
  };
  Contact *contact;
};

}

#endif //LABO_PAIR_H
