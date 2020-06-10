#ifndef LABO_LIGHT_FOREST_H
#define LABO_LIGHT_FOREST_H

#include "biome.h"
#include "../generator/tree_generator.h"

namespace labo::minecraft{
class LightForest: public Biome{
public:
  LightForest(int seed)
  : Biome(getNoiseParameters(), 60, 80, seed)
  {}

  Block getPlant(math::Random<std::minstd_rand> &rand) const override{
    return rand.intInRange(0, 10) > 8 ? Rose : TallGrass;
  }

  Block getTopBlock(math::Random<std::minstd_rand> &rand) const override{
    return Grass;
  }

  Block getUnderWaterBlock(math::Random<std::minstd_rand> &rand) const override{
    return rand.intInRange(0, 10) > 9 ? Sand : Dirt;
  }

  void makeTree(math::Random<std::minstd_rand> &rand, Chunk &chunk,
    int x, int y, int z) const override{
    makeOakTree(chunk, rand, x, y, z);
  }

private:
  NoiseParameters getNoiseParameters() override{
    NoiseParameters heightParams{};
    heightParams.octaves = 5;
    heightParams.amplitude = 100;
    heightParams.smoothness = 195;
    heightParams.heightOffset = -32;
    heightParams.roughness = 0.52;

    return heightParams;
  }
};
}

#endif //LABO_LIGHT_FOREST_H
