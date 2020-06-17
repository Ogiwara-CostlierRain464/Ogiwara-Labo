#ifndef LABO_BLOCK_APPEARANCE_H
#define LABO_BLOCK_APPEARANCE_H

#include <SFML/Graphics.hpp>
#include "../../minecraft/block/block.h"

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
  labo::math::Id<labo::minecraft::Block> id;

  sf::Vector2i texTopCoord;
  sf::Vector2i texSideCoord;
  sf::Vector2i texBottomCoord;

  BlockMeshType meshType;
  BlockShaderType shaderType;
};

const BlockAppearance AirAppear = BlockAppearance{
  {0},
  {0,0},
  {0,0},
  {0,0},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};

const BlockAppearance GrassAppear = BlockAppearance{
  {1},
  {0,0},
  {1,0},
  {2,0},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};

const BlockAppearance DirtAppear = BlockAppearance{
  {2},
  {2,0},
  {2,0},
  {2,0},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};

const BlockAppearance StoneAppear = BlockAppearance{
  {3},
  {3,0},
  {3,0},
  {3,0},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};

const BlockAppearance OakBarkAppear = BlockAppearance{
  {4},
  {5,0},
  {4,0},
  {5,0},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};

const BlockAppearance OakLeafAppear = BlockAppearance{
  {5},
  {6,0},
  {6,0},
  {6,0},
  BlockMeshType::Cube,
  BlockShaderType::Flora
};

const BlockAppearance SandAppear = BlockAppearance{
  {6},
  {7,0},
  {7,0},
  {7,0},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};

const BlockAppearance WaterAppear = BlockAppearance{
  {7},
  {8,0},
  {8,0},
  {8,0},
  BlockMeshType::Cube,
  BlockShaderType::Liquid
};

const BlockAppearance CactusAppear = BlockAppearance{
  {8},
  {9,0},
  {9,1},
  {9,0},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};

const BlockAppearance RoseAppear = BlockAppearance{
  {9},
  {10,0},
  {10,0},
  {10,0},
  BlockMeshType::X,
  BlockShaderType::Flora
};

const BlockAppearance TallGrassAppear = BlockAppearance{
  {10},
  {11,0},
  {11,0},
  {11,0},
  BlockMeshType::X,
  BlockShaderType::Flora
};

const BlockAppearance DeadShrubAppear = BlockAppearance{
  {11},
  {12,0},
  {12,0},
  {12,0},
  BlockMeshType::X,
  BlockShaderType::Flora
};

const BlockAppearance OakSaplingAppear = BlockAppearance{
  {12},
  {12,0},
  {12,0},
  {12,0},
  BlockMeshType::X,
  BlockShaderType::Flora
};


const BlockAppearance CobbleStoneAppear = BlockAppearance{
  {13},
  {3,1},
  {3,1},
  {3,1},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};

const BlockAppearance GlassAppear = BlockAppearance{
  {14},
  {7,1},
  {7,1},
  {7,1},
  BlockMeshType::Cube,
  BlockShaderType::Chunk_
};


}

#endif //LABO_BLOCK_APPEARANCE_H
