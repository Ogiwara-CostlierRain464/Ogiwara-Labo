#ifndef LABO_BLOCK_H
#define LABO_BLOCK_H

#include <SFML/System.hpp>
#include "../../math/id.h"
#include "../../math/non_copyable.h"

namespace labo::minecraft {

struct Block {
  labo::math::Id<Block> id;
  std::string name;
  bool isOpaque;
  bool isCollidable;
};

const Block Air = Block{
  math::Id<Block>{0},
  "Air",
  false, false
};

const Block Stone = Block{
  math::Id<Block>{3},
  "Stone",
  true, true
};


}

#endif //LABO_BLOCK_H
