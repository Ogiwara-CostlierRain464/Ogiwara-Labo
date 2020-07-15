#include <gtest/gtest.h>
#include "../src/math/glm.h"
#include <iostream>

using namespace glm;
using namespace std;
using namespace labo::math;

class GLM : public ::testing::Test{};

mat3 makeSample(){
  return mat3(
    vec3(-2, 0, 0),
    vec3(0, -5, 0),
    vec3(0, -8, -7)
  );
}

TEST_F(GLM, Prop){
  // GLMは行指向!!!!!!!!!
  auto sample = makeSample();
  EXPECT_EQ(sample[2][1], -8);
}

TEST_F(GLM, abs){
  mat3 mat = mat3(
    vec3(-2, 0, 0),
    vec3(0, -5, 0),
    vec3(0, -8, -7)
  );
  mat3 mat2 = mat3(
    vec3(2, 0, 0),
    vec3(0, 5, 0),
    vec3(0, 8, 7)
  );
  EXPECT_EQ(absPerElm(mat), mat2);
}

TEST_F(GLM, Transform3){
  auto move = vec3(1,2,3);
  auto trans = Transform3::from(makeSample(), move);

  EXPECT_EQ(trans.orientation[2][1], -8);
}

TEST_F(GLM, Transform3_inverse){
  auto move = vec3(1,2,3);
  auto trans = Transform3::from(makeSample(), move);

  EXPECT_EQ(trans.orientation[2][1], -8);
  EXPECT_EQ(trans.inverse().position, - transpose(makeSample()) * move);
}

TEST_F(GLM, Transform3_times){
  Transform3 trans = Transform3::from(mat3(1), vec3(0));
  Transform3 copy = trans;

  EXPECT_EQ((trans * copy).orientation[1][1], 1);
  EXPECT_EQ((trans * copy).orientation[1][2], 0);
}

TEST_F(GLM, crossVector){
  vec3 vec = vec3(1,2,3);
  mat3 mat = crossMatrix(vec);

  EXPECT_EQ(mat[1][0], vec[2]);
  EXPECT_EQ(mat[0][2], vec[1]);
}


TEST_F(GLM, crossVevfvctor){
  mat3 mat = mat3(1);

  EXPECT_EQ(mat[1][1], 1);
  EXPECT_EQ(mat[1][0], 0);

}

TEST_F(GLM, mat){
  // Unfortunately, my mac could not allocate double array[1024][1024],
  // so at here, I've changed the size of 2D array.
  double array[512][512];

  printf("(a): %lu\n", sizeof(array));
  printf("(b): %p\n", array[0] + 0);
  printf("(c): %p\n", array[0] + 1);
  printf("(d): %p\n", array[1] + 0);
  printf("(e): %p\n", array[1] + 1);
  printf("(f): %p\n", array[7] + 7);
  printf("(g): %p\n", array[511] + 511);

}
