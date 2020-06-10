#ifndef LABO_GRASSLAND_BIOME_H
#define LABO_GRASSLAND_BIOME_H

#include "biome.h"
#include "../generator/tree_generator.h"

namespace labo::minecraft{

class GrasslandBiome: public Biome{
public:
  GrasslandBiome(int seed)
    : Biome(getNoiseParameters(), 1000, 20, seed)
  {
  }

  Block getBeachBlock(
    math::Random<std::minstd_rand> &rand) const override{
    rand.intInRange(0, 10) > 2 ? Grass : Dirt;
  }

  Block getPlant(math::Random<std::minstd_rand> &rand) const override{
    return rand.intInRange(0, 10) > 6 ? Rose : TallGrass;
  }

  Block getTopBlock(math::Random<std::minstd_rand> &rand) const override{
    return Grass;
  }

  Block getUnderWaterBlock(math::Random<std::minstd_rand> &rand) const override{
    return rand.intInRange(0, 10) > 8 ? Dirt : Sand;
  }

  void makeTree(
    math::Random<std::minstd_rand> &rand, Chunk &chunk,
    int x, int y, int z) const override{
    makeOakTree(chunk, rand, x, y, z);
  }

private:
  NoiseParameters getNoiseParameters() override{
    NoiseParameters heightParams;
    heightParams.octaves = 9;
    heightParams.amplitude = 85;
    heightParams.smoothness = 235;
    heightParams.heightOffset = -20;
    heightParams.roughness = 0.51;

    return heightParams;
  }
};

}

#endif //LABO_GRASSLAND_BIOME_H
