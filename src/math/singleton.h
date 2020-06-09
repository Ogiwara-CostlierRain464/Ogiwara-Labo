#ifndef LABO_SINGLETON_H
#define LABO_SINGLETON_H

#include "non_movable.h"
#include "non_copyable.h"

namespace labo::math{

class Singleton: public NonMovable, public NonCopyable{
};

}

#endif //LABO_SINGLETON_H
