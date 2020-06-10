#ifndef LABO_TREE_GENERATOR_H
#define LABO_TREE_GENERATOR_H

#include "../../../math/random.h"

namespace labo::minecraft{

class Chunk;

void makeOakTree(
  Chunk &chunk,
  math::Random<std::minstd_rand> &rand,
  int x, int y, int z);

void makePalmTree(
  Chunk &chunk,
  math::Random<std::minstd_rand> &rand,
  int x, int y, int z);

void makeCactus(
  Chunk &chunk,
  math::Random<std::minstd_rand> &rand,
  int x, int y, int z);
}


#endif //LABO_TREE_GENERATOR_H
