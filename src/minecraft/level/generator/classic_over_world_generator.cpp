#include "classic_over_world_generator.h"
#include "../format/chunk.h"
#include "../../../math/smooth_inter_polation.h"

namespace {
  // 適当に固定
  const int seed = 325035;
}

labo::minecraft::ClassicOverWorldGenerator::ClassicOverWorldGenerator()
  :grassBiome(seed)
  , temperateForest(seed)
  , desertBiome(seed)
  , oceanBiome(seed)
  , lightForest(seed)
{
  setUpNoise();
}

void labo::minecraft::ClassicOverWorldGenerator::generateTerrainFor(
  labo::minecraft::Chunk &chunk_) {
  chunk = &chunk_;

  auto location = chunk->getLocation();
  random.setSeed((location.x ^ location.y) << 2);

  getBiomeMap();
  getHeightMap();

  auto maxHeight = heightMap.getMaxValue();

  maxHeight = std::max(maxHeight, WATER_LEVEL);
  setBlocks(maxHeight);
}

int labo::minecraft::ClassicOverWorldGenerator::getMinimumSpawnHeight() const noexcept {
  return WATER_LEVEL;
}

void labo::minecraft::ClassicOverWorldGenerator::setUpNoise() {
  static bool noiseGen = false;
  if(!noiseGen){
    noiseGen = true;

    NoiseParameters biomeParams{};
    biomeParams.octaves = 5;
    biomeParams.amplitude = 120;
    biomeParams.smoothness = 1035;
    biomeParams.heightOffset = 0;
    biomeParams.roughness = 0.75;

    biomeNoiseGen.setParameters(biomeParams);
  }
}

void labo::minecraft::ClassicOverWorldGenerator::setBlocks(int maxHeight) {
  std::vector<sf::Vector3i> trees;
  std::vector<sf::Vector3i> plants;

  for (int y = 0; y < maxHeight + 1; y++)
    for (int x = 0; x < CHUNK_SIZE; x++)
      for (int z = 0; z < CHUNK_SIZE; z++) {
        int height = heightMap.get(x, z);
        auto &biome = getBiome(x, z);

        if (y > height) {
          if (y <= WATER_LEVEL) {
            chunk->setBlock(x, y, z, Water);
          }
          continue;
        }
        else if (y == height) {
          if (y >= WATER_LEVEL) {
            if (y < WATER_LEVEL + 4) {
              chunk->setBlock(x, y, z,
                              biome.getBeachBlock(random));
              continue;
            }

            if (random.intInRange(0, biome.getTreeFrequency()) ==
                5) {
              trees.emplace_back(x, y + 1, z);
            }
            if (random.intInRange(0, biome.getPlantFrequency()) ==
                5) {
              plants.emplace_back(x, y + 1, z);
            }
            chunk->setBlock(
              x, y, z, getBiome(x, z).getTopBlock(random));
          }
          else {
            chunk->setBlock(x, y, z,
                            biome.getUnderWaterBlock(random));
          }
        }
        else if (y > height - 3) {
          chunk->setBlock(x, y, z, Dirt);
        }
        else {
          chunk->setBlock(x, y, z, Stone);
        }
      }

  for (auto &plant : plants) {
    int x = plant.x;
    int z = plant.z;

    auto block = getBiome(x, z).getPlant(random);
    chunk->setBlock(x, plant.y, z, block);
  }

  for (auto &tree : trees) {
    int x = tree.x;
    int z = tree.z;

    getBiome(x, z).makeTree(random, *chunk, x, tree.y, z);
  }
}

void labo::minecraft::ClassicOverWorldGenerator::getHeightIn(int xMin, int zMin, int xMax, int zMax) {
  auto getHeightAt = [&](int x, int z) {
    const Biome &biome = getBiome(x, z);

    return biome.getHeight(x, z, chunk->getLocation().x,
                           chunk->getLocation().y);
  };

  float bottomLeft = static_cast<float>(getHeightAt(xMin, zMin));
  float bottomRight = static_cast<float>(getHeightAt(xMax, zMin));
  float topLeft = static_cast<float>(getHeightAt(xMin, zMax));
  float topRight = static_cast<float>(getHeightAt(xMax, zMax));

  for (int x = xMin; x < xMax; ++x)
    for (int z = zMin; z < zMax; ++z) {
      if (x == CHUNK_SIZE)
        continue;
      if (z == CHUNK_SIZE)
        continue;

      float h = math::smoothInterpolation(
        bottomLeft, topLeft, bottomRight, topRight,
        static_cast<float>(xMin), static_cast<float>(xMax),
        static_cast<float>(zMin), static_cast<float>(zMax),
        static_cast<float>(x), static_cast<float>(z));

      // Making height map using noise.
      heightMap.get(x, z) = static_cast<int>(h);
    }
}

void labo::minecraft::ClassicOverWorldGenerator::getHeightMap() {
  constexpr static auto HALF_CHUNK = CHUNK_SIZE / 2;
  constexpr static auto CHUNK = CHUNK_SIZE;

  getHeightIn(0, 0, HALF_CHUNK, HALF_CHUNK);
  getHeightIn(HALF_CHUNK, 0, CHUNK, HALF_CHUNK);
  getHeightIn(0, HALF_CHUNK, HALF_CHUNK, CHUNK);
  getHeightIn(HALF_CHUNK, HALF_CHUNK, CHUNK, CHUNK);
}

void labo::minecraft::ClassicOverWorldGenerator::getBiomeMap() {
  auto location = chunk->getLocation();

  for (int x = 0; x < CHUNK_SIZE + 1; x++)
    for (int z = 0; z < CHUNK_SIZE + 1; z++) {
      double h = biomeNoiseGen.getHeight(x, z, location.x + 10,
                                           location.y + 10);
      // Making biome map using noise.
      biomeMap.get(x, z) = static_cast<int>(h);
    }
}

const labo::minecraft::Biome &labo::minecraft::ClassicOverWorldGenerator::getBiome(int x, int z) const {
  int biomeValue = biomeMap.get(x, z);

  if (biomeValue > 160) {
    return oceanBiome;
  }
  else if (biomeValue > 150) {
    return grassBiome;
  }
  else if (biomeValue > 130) {
    return lightForest;
  }
  else if (biomeValue > 120) {
    return temperateForest;
  }
  else if (biomeValue > 110) {
    return lightForest;
  }
  else if (biomeValue > 100) {
    return grassBiome;
  }
  else {
    return desertBiome;
  }
}

labo::minecraft::NoiseGenerator
labo::minecraft::ClassicOverWorldGenerator::biomeNoiseGen(seed * 2);

