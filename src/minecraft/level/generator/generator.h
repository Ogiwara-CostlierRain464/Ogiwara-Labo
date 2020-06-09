#ifndef LABO_GENERATOR_H
#define LABO_GENERATOR_H

namespace labo::minecraft{

class Chunk;

class Generator{
public:
  virtual void generateTerrainFor(Chunk &chunk) = 0;
  virtual int getMinimumSpawnHeight() const noexcept = 0;

  virtual ~Generator() = default;
};

}

#endif //LABO_GENERATOR_H
