#ifndef LABO_BIOME_H
#define LABO_BIOME_H

#include "noise_generator.h"
#include "../../block/block.h"
#include "../../../math/random.h"

namespace labo::minecraft{

class Chunk;

class Biome {
public:
  Biome(const NoiseParameters &parameters, int treeFeq, int plantFreq, int seed);
  virtual  ~Biome() = default;

  virtual Block getPlant(labo::math::Random<std::minstd_rand> &rand) const = 0;
  virtual Block getTopBlock(labo::math::Random<std::minstd_rand> &rand) const = 0;
  virtual Block getUnderWaterBlock(labo::math::Random<std::minstd_rand> &rand) const = 0;
  virtual Block getBeachBlock(labo::math::Random<std::minstd_rand> &rand) const;
  virtual void makeTree(labo::math::Random<std::minstd_rand> &rand, Chunk &chunk, int x, int y, int z) const = 0;

  int getHeight(int x, int z, int chunkX, int chunkZ) const;
  int getTreeFrequency() const noexcept;
  int getPlantFrequency() const noexcept;

protected:
  virtual NoiseParameters getNoiseParameters() = 0;

private:
  NoiseGenerator heightGenerator;
  int treeFreq;
  int plantFreq;
};
}

#endif //LABO_BIOME_H
