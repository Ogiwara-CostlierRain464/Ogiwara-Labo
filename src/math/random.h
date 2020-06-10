#ifndef LABO_RANDOM_H
#define LABO_RANDOM_H

#include <ctime>
#include <random>
#include "singleton.h"

namespace labo::math{

class RandomSingleton: public Singleton{
public:
  static RandomSingleton &get(){
    static RandomSingleton instance;
    return instance;
  }

  template <typename  T>
  T intInRange(T low, T high){
    static_assert(std::is_integral<T>::value, "Can't specify int type");
    std::uniform_int_distribution<T> dist(low, high);
    return dist(randomEngine);
  }

private:
  RandomSingleton(){
    //randomEngine.seed(static_cast<unsigned>(std::time(nullptr)));
    randomEngine.seed(static_cast<unsigned>(941));
    for(int i = 0; i < 5; i++){
      intInRange(i, i * 5);
    }
  }

  std::mt19937 randomEngine;
};

template <typename REngine = std::mt19937>
class Random{
public:
  Random(int n = std::time(nullptr)){
    randomEngine.seed(n);
    for(int i = 0; i < 5; i++){
      intInRange(i, i * 5);
    }
  }

  template <typename T>
  T intInRange(T low, T high){
    static_assert(std::is_integral<T>::value, "Can't specify int type");
    std::uniform_int_distribution<T> dist(low, high);
    return dist(randomEngine);
  }

  void setSeed(int seed){
    randomEngine.seed(seed);
  }

private:
  REngine randomEngine;
};

}

#endif //LABO_RANDOM_H
