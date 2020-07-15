#ifndef LABO_BASE_H
#define LABO_BASE_H

#include <cmath>

#define BENCH_START auto a = std::chrono::system_clock::now();
#define BENCH_END auto b = std::chrono::system_clock::now();double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(b-a).count();std::cout << elapsed << std::endl;


namespace labo::physics{

constexpr float EPSILON = 1e-5f;

inline float clamp(float v,float a,float b){
  return std::fmax(a, std::fmin(v, b));
}

}


#endif //LABO_BASE_H
