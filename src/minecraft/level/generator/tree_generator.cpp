#include "tree_generator.h"
#include "structure_builder.h"

void labo::minecraft::makeOakTree(
  Chunk &chunk,
  math::Random<std::minstd_rand> &rand,
  int x, int y, int z){
  StructureBuilder builder;

  int h = rand.intInRange(4, 7);
  int leafSize = 2;

  int newY = h + y;
  builder.fill(
    newY, x - leafSize,
    x + leafSize, z - leafSize,
    z + leafSize, OakLeaf);
  builder.fill(
    newY - 1, x - leafSize,
    x + leafSize, z - leafSize,
    z + leafSize, OakLeaf);

  for(int zLeaf = -leafSize + 1; zLeaf <= leafSize - 1; zLeaf++){
    builder.addBlock(x, newY + 1, z + zLeaf, OakLeaf);
  }
  for(int xLeaf = -leafSize + 1; xLeaf <= leafSize - 1; xLeaf++){
    builder.addBlock(x + xLeaf, newY + 1, z, OakLeaf);
  }

  builder.makeColumn(x, z, y, h, OakBark);
  builder.build(chunk);
}

void labo::minecraft::makePalmTree(
  Chunk &chunk,
  math::Random<std::minstd_rand> &rand,
  int x, int y, int z){
  StructureBuilder builder;

  int height = rand.intInRange(7, 9);
  int diameter = rand.intInRange(4, 6);

  for (int xLeaf = -diameter; xLeaf < diameter; xLeaf++) {
    builder.addBlock(xLeaf + x, y + height, z, OakLeaf);
  }
  for (int zLeaf = -diameter; zLeaf < diameter; zLeaf++) {
    builder.addBlock(x, y + height, zLeaf + z, OakLeaf);
  }

  builder.addBlock(x, y + height - 1, z + diameter, OakLeaf);
  builder.addBlock(x, y + height - 1, z - diameter, OakLeaf);
  builder.addBlock(x + diameter, y + height - 1, z, OakLeaf);
  builder.addBlock(x - diameter, y + height - 1, z, OakLeaf);
  builder.addBlock(x, y + height + 1, z, OakLeaf);

  builder.makeColumn(x, z, y, height, OakBark);
  builder.build(chunk);
}

void labo::minecraft::makeCactus(
  Chunk &chunk,
  math::Random<std::minstd_rand> &rand,
  int x, int y, int z){

  StructureBuilder builder;
  builder.makeColumn(x, z, y, rand.intInRange(4, 7), Cactus);
  builder.build(chunk);
}

