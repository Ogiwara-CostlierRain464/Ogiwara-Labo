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

}

#endif //LABO_BLOCK_APPEARANCE_H