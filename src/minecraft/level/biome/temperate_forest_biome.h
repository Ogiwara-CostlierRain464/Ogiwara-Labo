#ifndef LABO_TEMPERATE_FOREST_BIOME_H
#define LABO_TEMPERATE_FOREST_BIOME_H

#include "biome.h"
#include "../generator/tree_generator.h"

namespace labo::minecraft{

class TemperateForestBiome: public Biome{
public:
  TemperateForestBiome(int seed)
  : Biome(getNoiseParameters(), 55, 75, seed)
  {
  }

  Block getPlant(math::Random<std::minstd_rand> &rand) const override{
    return TallGrass;
  }

  Block getTopBlock(math::Random<std::minstd_rand> &rand) const override{
    return rand.intInRange(0, 10) < 8 ? Grass : Dirt;
  }

  Block getUnderWaterBlock(math::Random<std::minstd_rand> &rand) const override{
    return rand.intInRange(0, 10) > 8 ? Dirt : Sand;
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
    heightParams.heightOffset = -30;
    heightParams.roughness = 0.52;

    return heightParams;
  }
};

}

#endif //LABO_TEMPERATE_FOREST_BIOME_H
