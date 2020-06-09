#include "experimental_space_generator.h"
#include "../format/chunk.h"

void labo::minecraft::ExperimentalSpaceGenerator
::generateTerrainFor(Chunk &chunk) {
  for(int x = 0; x < CHUNK_SIZE; x++){
    for(int z = 0; z < CHUNK_SIZE; z++){
      chunk.setBlock(x, 0, z, Stone);
      chunk.setBlock(x, 1, z, Stone);
      chunk.setBlock(x, 2, z, Stone);
      chunk.setBlock(x, 3, z, Stone);
      chunk.setBlock(x, 4, z, Stone);
    }
  }
}

int labo::minecraft::ExperimentalSpaceGenerator::getMinimumSpawnHeight() const noexcept {
  return 2;
}
