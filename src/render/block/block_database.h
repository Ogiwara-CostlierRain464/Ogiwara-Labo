#ifndef LABO_BLOCK_DATABASE_H
#define LABO_BLOCK_DATABASE_H

#include "../../math/singleton.h"
#include "block_appearance.h"
#include "../../math/id.h"
#include "../../minecraft/block/block.h"
#include "../texture/texture_atlas.h"

namespace labo::render{

class BlockDatabase: public labo::math::Singleton{
public:
  using BlockId = labo::math::Id<labo::minecraft::Block>;

  static BlockDatabase &get(){
    static BlockDatabase instance;
    return instance;
  }

  [[nodiscard]]
  const BlockAppearance &getBlockAppearance(BlockId id) const{
    switch (id.value){
      case 0:
        return AirAppear;
      case 3:
        return StoneAppear;
      default:
        throw std::runtime_error("NOT IMPLEMENTED");
    }
  }

  TextureAtlas textureAtlas;
private:
  BlockDatabase(): textureAtlas("DefaultPack2")
  {}
};

}

#endif //LABO_BLOCK_DATABASE_H
