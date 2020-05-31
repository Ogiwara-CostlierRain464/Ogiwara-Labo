#ifndef LABO_APPLICATION_H
#define LABO_APPLICATION_H
#include "config.h"
#include "../render/camera.h"
#include "../render/render_master.h"
#include <SFML/Graphics.hpp>

namespace labo::app{

class Application {
public:
  explicit Application(const Config &config);

  void mainLoop();
  void handleGUIInput();

private:
  const Config &config;
  labo::render::Camera camera;
  labo::render::RenderMaster renderMaster;
  sf::RenderWindow window;
};

}

#endif //LABO_APPLICATION_H
