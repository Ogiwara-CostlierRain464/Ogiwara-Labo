#ifndef LABO_CLASSIC_OVER_WORLD_GENERATOR_H
#define LABO_CLASSIC_OVER_WORLD_GENERATOR_H

#include "generator.h"
#include "../biome/biome.h"
#include "../../../math/array_2d.h"
#include "../biome/grassland_biome.h"
#include "../biome/desert_biome.h"
#include "../biome/ocean_biome.h"
#include "../biome/light_forest.h"
#include "../biome/temperate_forest_biome.h"

namespace labo::minecraft{

class Chunk;

class ClassicOverWorldGenerator: public TerrainGenerator{
public:
  ClassicOverWorldGenerator();

  void generateTerrainFor(Chunk &chunk) override;

  [[nodiscard]]
  int getMinimumSpawnHeight() const noexcept override;

private:
  static void setUpNoise();

  void setBlocks(int maxHeight);

  void getHeightIn(int xMin, int zMin, int xMax, int zMax);
  void getHeightMap();
  void getBiomeMap();

  [[nodiscard]]
  const Biome &getBiome(int x, int z) const;

  math::Array2D<int, CHUNK_SIZE> heightMap;
  math::Array2D<int, CHUNK_SIZE + 1> biomeMap;

  math::Random<std::minstd_rand> random;

  static NoiseGenerator biomeNoiseGen;

  GrasslandBiome grassBiome;
  TemperateForestBiome temperateForest;
  DesertBiome desertBiome;
  OceanBiome oceanBiome;
  LightForest lightForest;

  Chunk *chunk = nullptr;

};

}

#endif //LABO_CLASSIC_OVER_WORLD_GENERATOR_H
