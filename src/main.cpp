#include "application/config.h"
#include "application/application.h"

using namespace labo::app;

int main(){
  Config config{};
  Application app(config);
  app.mainLoop();
}