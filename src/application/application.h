#ifndef LABO_APPLICATION_H
#define LABO_APPLICATION_H
#include "config.h"

namespace labo::app{

class Application {
public:
  explicit Application(const Config &config);

  void mainLoop();

private:
  const Config &config;
};

}

#endif //LABO_APPLICATION_H
