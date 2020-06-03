#ifndef LABO_CONST_H
#define LABO_CONST_H

namespace labo::minecraft{

constexpr int CHUNK_SIZE = 16;
constexpr int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
constexpr int CHUNK_VOLUME = CHUNK_AREA * CHUNK_SIZE;

constexpr int WATER_LEVEL = 64;
}

#endif //LABO_CONST_H
