#ifndef LABO_BIOME_H
#define LABO_BIOME_H

namespace labo::minecraft{

class Biome {
public:
  Biome(int treeFeq, int plantFreq, int seed);
  virtual  ~Biome() = default;

  virtual getPlant();
};
}

#endif //LABO_BIOME_H
