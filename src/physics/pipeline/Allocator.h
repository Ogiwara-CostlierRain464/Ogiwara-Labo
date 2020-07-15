#ifndef LABO_ALLOCATOR_H
#define LABO_ALLOCATOR_H

#include <cstddef>

namespace labo::physics{

class Allocator{
public:
  virtual void *allocate(size_t bytes) = 0;
  virtual void deallocate(void *p) = 0;
};

}

#endif //LABO_ALLOCATOR_H
