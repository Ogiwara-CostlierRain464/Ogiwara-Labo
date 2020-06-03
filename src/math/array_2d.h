#ifndef LABO_ARRAY_2D_H
#define LABO_ARRAY_2D_H

#include <algorithm>
#include <array>

namespace labo::math{

template <typename T, int WIDTH>
class Array2D{
  using Array = std::array<T, WIDTH * WIDTH>;

public:
  T &get(int x, int z){
    return array[x * WIDTH + z];
  }

  const T &get(int x, int z)const{
    return array[x * WIDTH + z];
  }

  T &getMaxValue(){
    return *std::max_element(array.begin(), array.end());
  }

  void setAll(T val){
    array.fill(val);
  }

private:
  Array array;
};

}

#endif //LABO_ARRAY_2D_H
