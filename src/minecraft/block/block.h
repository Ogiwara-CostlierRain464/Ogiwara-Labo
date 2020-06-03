#ifndef LABO_BLOCK_H
#define LABO_BLOCK_H

#include <SFML/System.hpp>
#include "../../math/id.h"
#include "../../math/non_copyable.h"

namespace labo::minecraft {

enum BlockMeshType{
  Cube, X
};

enum BlockShaderType{
  Chunk, Liquid, Flora
};

struct BlockMetaData{
  sf::Vector2i texTopCoord;
  sf::Vector2i texSideCoord;
  sf::Vector2i texBottomCoord;

  BlockMeshType meshType;
  BlockShaderType shaderType;

  bool isOpaque;
  bool isCollidable;
};

struct Block {
  Block() = default;

  explicit Block(labo::math::Id<Block> id, BlockMetaData metaData)
    : id(id)
    , metaData(metaData)
  {}

  [[nodiscard]]
  virtual bool isOpaque() const{
    return metaData.isOpaque;
  }

  labo::math::Id<Block> id;
  BlockMetaData metaData;
};

const Block Air = Block(math::Id<Block>{0}, BlockMetaData{
  sf::Vector2i(0,0),
  sf::Vector2i(0,0),
  sf::Vector2i(0,0),

  Cube, Chunk,

  false, false
});

const Block Stone = Block(math::Id<Block>{3}, BlockMetaData{
  sf::Vector2i(3,0),
  sf::Vector2i(3,0),
  sf::Vector2i(3,0),

  Cube, Chunk,

  true, true
});

}

#endif //LABO_BLOCK_H
