#ifndef LABO_CLASSIC_OVER_WORLD_GENERATOR_H
#define LABO_CLASSIC_OVER_WORLD_GENERATOR_H

#include "generator.h"

namespace labo::minecraft{

class ClassicOverWorldGenerator: public TerrainGenerator{
public:
  ClassicOverWorldGenerator();

  void generateTerrainFor(Chunk &chunk) override;

  [[nodiscard]]
  int getMinimumSpawnHeight() const noexcept override;


};

}

#endif //LABO_CLASSIC_OVER_WORLD_GENERATOR_H
