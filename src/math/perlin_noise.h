#ifndef LABO_PERLIN_NOISE_H
#define LABO_PERLIN_NOISE_H

#include <cmath>

namespace labo::math{

static double getNoise(int n, int seed){
  n += seed;
  n = (n << 13) ^ n;
  auto newN = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;

  return 1.0 - ((double)newN / 1073741824.0);
}

static double getNoise(double x, double z, int seed){
  return getNoise((int)(x + z * 57.0), seed);
}

static double lerp(double a, double b, double z){
  double  mu2 = (1 - std::cos(z * M_PI)) / 2;
  return (a * (1 - mu2) + b * mu2);
}

static double perlinNoise(double x, double z, int seed){
  auto floorX = (double)((int)x);
  auto floorZ = (double)((int)x);

  double s = getNoise(floorX, floorZ, seed);
  double t = getNoise(floorX + 1, floorZ, seed);
  double u = getNoise(floorX, floorZ + 1, seed);
  double v = getNoise(floorX + 1, floorZ + 1, seed);

  auto rec1 = lerp(s, t, x - floorX);
  auto rec2 = lerp(u, v, x - floorX);
  auto rec3 = lerp(rec1, rec2, z - floorZ);

  return rec3;
}

}

#endif //LABO_PERLIN_NOISE_H
