#include "chunk_mesh_builder.h"
#include "chunk_mesh.h"
#include "block/block_database.h"

using labo::minecraft::CHUNK_SIZE;
using labo::minecraft::CHUNK_VOLUME;
using labo::minecraft::Block;
using labo::minecraft::SubChunk;
using labo::minecraft::Air;
using labo::render::BlockDatabase;
using labo::render::BlockAppearance;
using std::array;

namespace {
  struct AdjacentBlockPositions{
    sf::Vector3i up;
    sf::Vector3i down;
    sf::Vector3i left;
    sf::Vector3i right;
    sf::Vector3i front;
    sf::Vector3i back;

    void update(int x, int y, int z){
      up = {x, y + 1, z};
      down = {x, y - 1, z};
      left = {x - 1, y, z};
      right = {x + 1, y, z};
      front = {x, y, z + 1};
      back = {x, y, z - 1};
    }
  };

  const array<GLfloat, 12> frontFace{
    0,0,1,
    1,0,1,
    1,1,1,
    0,1,1
  };

  const array<GLfloat, 12> backFace{
    1, 0, 0,
    0, 0, 0,
    0, 1, 0,
    1, 1, 0,
  };

  const std::array<GLfloat, 12> leftFace{
    0, 0, 0,
    0, 0, 1,
    0, 1, 1,
    0, 1, 0,
  };

  const std::array<GLfloat, 12> rightFace{
    1, 0, 1,
    1, 0, 0,
    1, 1, 0,
    1, 1, 1,
  };

  const std::array<GLfloat, 12> topFace{
    0, 1, 1,
    1, 1, 1,
    1, 1, 0,
    0, 1, 0,
  };

  const std::array<GLfloat, 12> bottomFace{
    0, 0, 0,
    1, 0, 0,
    1, 0, 1,
    0, 0, 1
  };

  const std::array<GLfloat, 12> xFace1{
    0, 0, 0,
    1, 0, 1,
    1, 1, 1,
    0, 1, 0,
  };

  const std::array<GLfloat, 12> xFace2{
    0, 0, 1,
    1, 0, 0,
    1, 1, 0,
    0, 1, 1,
  };

  constexpr GLfloat LIGHT_TOP = 1.f;
  constexpr GLfloat LIGHT_X = 0.8f; // left,rightの光源
  constexpr GLfloat LIGHT_Z = 0.6f; // front,backの光源
  constexpr GLfloat LIGHT_BOT = 0.4f;
}

labo::render::ChunkMeshBuilder::ChunkMeshBuilder(
  labo::minecraft::SubChunk *subChunk,
  labo::render::ChunkMeshCollection *collection)
  : subChunk(subChunk)
  , collection(collection)
{}

void labo::render::ChunkMeshBuilder::buildMesh() {
  AdjacentBlockPositions directions;
  blockPtr = subChunk->blocksFirstPtr();
  faces = 0;
  for(int i =0; i < CHUNK_VOLUME; i++){
    int x = i % CHUNK_SIZE;
    int y = i / (CHUNK_SIZE * CHUNK_SIZE);
    int z = (i / CHUNK_SIZE) % CHUNK_SIZE;

    if(!shouldMakeLayer(y)){
      continue;
    }

    Block block_ = *blockPtr;
    BlockAppearance appearance = BlockDatabase::get()
      .getBlockAppearance(block_.id);

    blockPtr++;

    sf::Vector3i position(x,y,z);
    setActiveMesh(block_);

    if(block_.id == Air.id){
      // 描画する必要無し
      continue;
    }

    blockAppearPtr = &appearance;

    if(appearance.meshType == BlockMeshType::X){
      addXBlockToMesh(appearance.texTopCoord, position);
      continue;
    }

    directions.update(x,y,z);

    // y = 0でないなら、下面を描画
    if(subChunk->getLocation().y != 0 || y != 0){
      tryAddFaceToMesh(
        bottomFace,
        appearance.texBottomCoord,
        position,
        directions.down,
        LIGHT_BOT
        );
    }
    tryAddFaceToMesh(
      topFace,
      appearance.texTopCoord,
      position,
      directions.up,
      LIGHT_TOP
      );
    tryAddFaceToMesh(
      leftFace,
      appearance.texSideCoord,
      position,
      directions.left,
      LIGHT_X
    );
    tryAddFaceToMesh(
      rightFace,
      appearance.texSideCoord,
      position,
      directions.right,
      LIGHT_X
    );
    tryAddFaceToMesh(
      frontFace,
      appearance.texSideCoord,
      position,
      directions.front,
      LIGHT_Z
    );
    tryAddFaceToMesh(
      backFace,
      appearance.texSideCoord,
      position,
      directions.back,
      LIGHT_Z
    );

  }
}

void labo::render::ChunkMeshBuilder::setActiveMesh(
  labo::minecraft::Block block_) {
  BlockAppearance appearance = BlockDatabase::get()
    .getBlockAppearance(block_.id);

  switch(appearance.shaderType){
    case BlockShaderType::Chunk_:
      activeMesh = &collection->solidMesh;
      break;
    case BlockShaderType::Liquid:
      activeMesh = &collection->waterMesh;
      break;
    case BlockShaderType::Flora:
      activeMesh = &collection->floraMesh;
      break;
  }
}

void labo::render::ChunkMeshBuilder::addXBlockToMesh(
  const sf::Vector2i &textureCoords,
  const sf::Vector3i &blockPosition) {
  faces++;
  auto texCoords =
    BlockDatabase::get().textureAtlas.getTexture(textureCoords);

  activeMesh->addFace(
    xFace1, texCoords,
    subChunk->getLocation(),
    blockPosition,
    LIGHT_X
    );

  activeMesh->addFace(
    xFace2, texCoords,
    subChunk->getLocation(),
    blockPosition,
    LIGHT_X
  );
}

void labo::render::ChunkMeshBuilder::tryAddFaceToMesh(
  const std::array<GLfloat, 12> &blockFace,
  const sf::Vector2i &textureCoords,
  const sf::Vector3i &blockPosition,
  const sf::Vector3i &blockFacing,
  GLfloat cardinalLight) {
  if(shouldMakeFace(blockFacing, *blockAppearPtr)){
    faces++;
    auto texCoords =
      BlockDatabase::get().textureAtlas.getTexture(textureCoords);

    activeMesh->addFace(
      blockFace,
      texCoords,
      subChunk->getLocation(),
      blockPosition,
      cardinalLight
      );
  }
}

bool labo::render::ChunkMeshBuilder::shouldMakeFace(
  const sf::Vector3i &adjBlock,
  const BlockAppearance &blockAppear
) {
  auto block_ = subChunk->getBlock(adjBlock.x, adjBlock.y, adjBlock.z);

  if(block_.id == Air.id){
    return true;
  } else if((!block_.isOpaque && (block_.id != blockAppearPtr->id))){
    return true;
  }
  return false;
}

bool labo::render::ChunkMeshBuilder::shouldMakeLayer(int y) {
  auto adjIsSolid = [&](int dx, int dz){
    const SubChunk &subChunk_ = subChunk->getAdjacentSubChunk(dx, dz);
    return subChunk_.getLayer(y).isAllSolid();
  };

  return (!subChunk->getLayer(y).isAllSolid())
         || (!subChunk->getLayer(y + 1).isAllSolid())
         || (!subChunk->getLayer(y - 1).isAllSolid())
         || (!adjIsSolid(1,0))
         || (!adjIsSolid(0,1))
         || (!adjIsSolid(-1, 0))
         || (!adjIsSolid(0, -1));
}

