#include "biome.h"

labo::minecraft::Biome::Biome(
  int treeFeq, int plantFreq,int seed)
  : heightGenerator(seed)
  , treeFreq(treeFeq)
  , plantFreq(plantFreq)
{}

int labo::minecraft::Biome::getHeight(int x, int z, int chunkX, int chunkZ) const {
  return (int) heightGenerator.getHeight(x, z, chunkX, chunkZ);
}

int labo::minecraft::Biome::getTreeFrequency() const noexcept {
  return treeFreq;
}

int labo::minecraft::Biome::getPlantFrequency() const noexcept {
  return plantFreq;
}
