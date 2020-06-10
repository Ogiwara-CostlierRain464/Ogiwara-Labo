#include <gtest/gtest.h>
#include <memory>

using namespace std;

class Pointer: public ::testing::Test{};

TEST_F(Pointer, raw){
  int *ptr = new int(10);

  for(int i = 0;i < 10; i++){
    *ptr += i;
  }
}

class Hoge{
private:
  unique_ptr<int> ptr;
public:
  Hoge(int val): ptr(new int(val)){}
  int getValue()const{return *ptr;}
};

TEST_F(Pointer, unique_ptr){
  Hoge hoge(10);
  //Hoge hoge1(hoge); ERROR
  Hoge hoge1(std::move(hoge));

}

TEST_F(Pointer, shared_ptr){
  shared_ptr<int> ptr;
  {
    shared_ptr<int> ptr2(new int(0));
    ptr = ptr2;

    *ptr += 10;
    *ptr2 += 10;
  }

  // can use ptr at here.
}

struct Hoge2{
  shared_ptr<Hoge2> ptr;
};

TEST_F(Pointer, circular){
  shared_ptr<Hoge2> hoge1 = make_shared<Hoge2>();
  shared_ptr<Hoge2> hoge2 = make_shared<Hoge2>();

  hoge1->ptr = hoge2;
  hoge2->ptr = hoge1;
}

struct Hoge3{
  unique_ptr<Hoge3> ptr;
};

TEST_F(Pointer, circular_){
  unique_ptr<Hoge3> hoge1 = make_unique<Hoge3>();
  unique_ptr<Hoge3> hoge2 = make_unique<Hoge3>();

  hoge1->ptr = std::move(hoge2);
  hoge1->ptr->ptr = std::move(hoge1);
}

class Hoge4{
public:
  weak_ptr<Hoge4> ptr;
};

TEST_F(Pointer, weak_ptr){
  shared_ptr<Hoge4> hoge = make_shared<Hoge4>();
  shared_ptr<Hoge4> hoge2 = make_shared<Hoge4>();

  hoge->ptr = hoge2;
  hoge2->ptr = hoge;
}