#ifndef LABO_STRUCTURE_BUILDER_H
#define LABO_STRUCTURE_BUILDER_H

#include "../../../math/id.h"
#include "../../block/block.h"
#include "../format/chunk.h"

namespace labo::minecraft{

class StructureBuilder{
  using BlockId = math::Id<Block>;

  struct HelperBlock{
    Block block;
    int x, y, z;

    HelperBlock(Block block, int x, int y, int z)
      : block(block)
      , x(x)
      , y(y)
      , z(z)
    {}
  };

public:
  void build(Chunk &chunk){
    for(auto &block: blocks){
      chunk.setBlock(block.x, block.y, block.z, block.block);
    }
  }

  void makeColumn(
    int x, int z, int yStart,
    int height, Block block){
    for(int y = yStart; y < yStart + height; y++){
      addBlock(x, y, z, block);
    }
  }

  void makeRowX(
    int xStart, int xEnd, int y, int z, Block block){
    for(int x = xStart; x <= xEnd; x++){
      addBlock(x, y, z, block);
    }
  }

  void makeRowZ(
    int zStart, int zEnd, int x, int y, Block block){
    for(int z = zStart; z <= zEnd; z++){
      addBlock(x, y, z, block);
    }
  }

  void fill(
    int y, int xStart, int xEnd,
    int zStart, int zEnd, Block block){
    for(int x = xStart; x < xEnd; x++){
      for(int z = zStart; z < zEnd; z++){
        addBlock(x, y, z, block);
      }
    }
  }

  void addBlock(int x, int y, int z, Block block){
    blocks.emplace_back(block, x, y, z);
  }

private:
  std::vector<HelperBlock> blocks;
};
}

#endif //LABO_STRUCTURE_BUILDER_H
