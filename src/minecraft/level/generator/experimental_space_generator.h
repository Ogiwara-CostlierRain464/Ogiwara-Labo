#ifndef LABO_EXPERIMENTAL_SPACE_GENERATOR_H
#define LABO_EXPERIMENTAL_SPACE_GENERATOR_H

#include "generator.h"

namespace labo::minecraft{

class ExperimentalSpaceGenerator: public Generator{
public:
  void generateTerrainFor(Chunk &chunk) override;
  int getMinimumSpawnHeight() const noexcept override;
};

}

#endif //LABO_EXPERIMENTAL_SPACE_GENERATOR_H
