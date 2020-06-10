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
      case 1:
        return GrassAppear;
      case 2:
        return DirtAppear;
      case 3:
        return StoneAppear;
      case 4:
        return OakBarkAppear;
      case 5:
        return OakLeafAppear;
      case 6:
        return SandAppear;
      case 7:
        return WaterAppear;
      case 8:
        return CactusAppear;
      case 9:
        return RoseAppear;
      case 10:
        return TallGrassAppear;
      case 11:
        return DeadShrubAppear;
      case 12:
        return OakSaplingAppear;
      case 13:
        return CobbleStoneAppear;
      case 14:
        return GlassAppear;
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
