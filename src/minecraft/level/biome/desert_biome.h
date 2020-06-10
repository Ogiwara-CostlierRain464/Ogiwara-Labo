#ifndef LABO_DESERT_BIOME_H
#define LABO_DESERT_BIOME_H

#include "biome.h"
#include "../generator/tree_generator.h"

namespace labo::minecraft{

class DesertBiome: public Biome{
public:
  explicit DesertBiome(int seed)
    : Biome(getNoiseParameters(), 1350, 500, seed)
  {}

  Block getPlant(labo::math::Random<std::minstd_rand> &rand) const override {
    return DeadShrub;
  }

  Block getTopBlock(labo::math::Random<std::minstd_rand> &rand) const override {
    return Sand;
  }

  Block getUnderWaterBlock(labo::math::Random<std::minstd_rand> &rand) const override {
    return Sand;
  }

  void makeTree(labo::math::Random<std::minstd_rand> &rand,
    Chunk &chunk, int x, int y, int z) const override {
    if(y < WATER_LEVEL + 15){
      if(rand.intInRange(0, 100) > 75){
        makePalmTree(chunk, rand, x, y, z);
      }else{
        makeCactus(chunk, rand, x, y, z);
      }
    }else{
      makeCactus(chunk, rand, x, y, z);
    }
  }

  NoiseParameters getNoiseParameters() override {
    NoiseParameters parameters{};
    parameters.octaves = 9;
    parameters.amplitude = 80;
    parameters.smoothness = 335;
    parameters.heightOffset = -7;
    parameters.roughness = 0.56;

    return parameters;
  }
};

}

#endif //LABO_DESERT_BIOME_H
