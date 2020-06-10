#ifndef LABO_BLOCK_H
#define LABO_BLOCK_H

#include <SFML/System.hpp>
#include "../../math/id.h"
#include "../../math/non_copyable.h"

namespace labo::minecraft {

struct Block {
  labo::math::Id<Block> id;
  bool isOpaque; // 不透明
  bool isCollidable; // 衝突判定
};

const Block Air = Block{
  math::Id<Block>{0},
  false, false
};

const Block Grass = Block{
  math::Id<Block>{1},
  true, true
};

const Block Dirt = Block{
  math::Id<Block>{2},
  true, true
};

const Block Stone = Block{
  math::Id<Block>{3},
  true, true
};


}

#endif //LABO_BLOCK_H
