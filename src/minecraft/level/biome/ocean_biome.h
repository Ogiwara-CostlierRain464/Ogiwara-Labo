#ifndef LABO_OCEAN_BIOME_H
#define LABO_OCEAN_BIOME_H

#include "biome.h"
#include "../generator/tree_generator.h"

namespace labo::minecraft{

class OceanBiome: public Biome{
public:
  OceanBiome(int seed)
    : Biome(getNoiseParameters(), 50, 100, seed)
  {}

  Block getPlant(math::Random<std::minstd_rand> &rand) const override{
    return rand.intInRange(0, 10) > 6 ? Rose : TallGrass;
  }

  Block getTopBlock(math::Random<std::minstd_rand> &rand) const override{
    return Grass;
  }

  Block getUnderWaterBlock(math::Random<std::minstd_rand> &rand) const override{
    return Sand;
  }

  void makeTree(math::Random<std::minstd_rand> &rand, Chunk &chunk,
    int x, int y, int z) const override{
    rand.intInRange(0, 5) < 3
    ? makePalmTree(chunk, rand, x, y, z)
    : makeOakTree(chunk, rand, x, y, z);
  }

private:
  NoiseParameters getNoiseParameters() override{
    NoiseParameters heightParams{};
    heightParams.octaves = 7;
    heightParams.amplitude = 43;
    heightParams.smoothness = 55;
    heightParams.heightOffset = 0;
    heightParams.roughness = 0.50;

    return heightParams;
  }
};

}

#endif //LABO_OCEAN_BIOME_H
