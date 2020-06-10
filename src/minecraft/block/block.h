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

const Block OakBark = Block{
  math::Id<Block>{4},
  true, true
};

const Block OakLeaf = Block{
  math::Id<Block>{5},
  false, true
};

const Block Sand = Block{
  math::Id<Block>{6},
  true, true
};

const Block Water = Block{
  math::Id<Block>{7},
  false, false
};

const Block Cactus = Block{
  math::Id<Block>{8},
  true, true
};

const Block Rose = Block{
  math::Id<Block>{9},
  false, false
};

const Block TallGrass = Block{
  math::Id<Block>{10},
  false, false
};

const Block DeadShrub = Block{
  math::Id<Block>{11},
  false, false
};

const Block OakSapling = Block{
  math::Id<Block>{12},
  false, false
};

const Block CobbleStone = Block{
  math::Id<Block>{13},
  true, false
};

const Block Glass = Block{
  math::Id<Block>{14},
  false, true
};


}

#endif //LABO_BLOCK_H
