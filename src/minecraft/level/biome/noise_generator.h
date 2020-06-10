#ifndef LABO_NOISE_GENERATOR_H
#define LABO_NOISE_GENERATOR_H

#include <cmath>
#include "../const.h"
#include "../../../math/perlin_noise.h"

namespace labo::minecraft{

struct NoiseParameters{
  int octaves;
  int amplitude;
  int smoothness;
  int heightOffset;

  double roughness;
};

class NoiseGenerator{
public:
  explicit NoiseGenerator(int seed)
    : seed(seed)
  {
    noiseParameters.octaves = 7;
    noiseParameters.amplitude = 70;
    noiseParameters.smoothness = 235;
    noiseParameters.heightOffset = -5;
    noiseParameters.roughness = 0.53;
  }

  [[nodiscard]]
  double getHeight(
    int x, int z,
    int chunkX, int chunkZ) const noexcept{
    auto newX = (x + (chunkX * CHUNK_SIZE));
    auto newZ = (z + (chunkZ * CHUNK_SIZE));

    if(newX < 0 || newZ < 0){
      return WATER_LEVEL - 1;
    }

    auto totalValue = 0.0;

    for(auto a = 0; a < noiseParameters.octaves - 1; a++){
      auto frequency = std::pow(2.0, a);
      auto amplitude = std::pow(noiseParameters.roughness, a);
      totalValue +=
        labo::math::perlinNoise(
          ((double)newX) * frequency / noiseParameters.smoothness,
          ((double)newZ) * frequency / noiseParameters.smoothness,
          seed
          ) * amplitude;
    }

    auto val = (((totalValue / 2.1) + 1.2) * noiseParameters.amplitude)
               + noiseParameters.heightOffset;

    return val > 0 ? val : 1;
  }

private:
  NoiseParameters noiseParameters{};
  int seed;
};

}

#endif //LABO_NOISE_GENERATOR_H
