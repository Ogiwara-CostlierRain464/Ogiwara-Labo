#ifndef LABO_BLOCK_APPEARANCE_H
#define LABO_BLOCK_APPEARANCE_H

#include <SFML/Graphics.hpp>

/**
 * Blockの具体的な見た目について
 */
namespace labo::render{

enum BlockMeshType{
  Cube, X // 草とか花とか、Xの形をした物
};

enum BlockShaderType{
  Chunk_, Liquid, Flora
};

struct BlockAppearance{
  sf::Vector2i texTopCoord;
  sf::Vector2i texSideCoord;
  sf::Vector2i texBottomCoord;

  BlockMeshType meshType;
  BlockShaderType shaderType;
};

const BlockAppearance AirAppear = BlockAppearance{
  {0,0},
  {0,0},
  {0,0},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};

const BlockAppearance GrassAppear = BlockAppearance{
  {0,0},
  {1,0},
  {2,0},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};

const BlockAppearance DirtAppear = BlockAppearance{
  {2,0},
  {2,0},
  {2,0},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};

const BlockAppearance StoneAppear = BlockAppearance{
  {3,0},
  {3,0},
  {3,0},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};



}

#endif //LABO_BLOCK_APPEARANCE_H
