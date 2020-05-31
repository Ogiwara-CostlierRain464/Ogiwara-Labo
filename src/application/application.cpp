#include "application.h"
#include <SFML/Graphics.hpp>

using sf::Clock;
using sf::Time;
using labo::render::Camera;
using labo::render::CameraConfig;


labo::app::Application::Application(const labo::app::Config &config)
  : config(config)
  , camera(Camera(CameraConfig{1200, 800, 90}))
{

}

void labo::app::Application::mainLoop() {
  Clock dtTimer;

  while(window.isOpen()){
    auto deltaTime = dtTimer.restart();

    // Play STate
    camera.update();

    renderMaster.finish(window, camera);

    handleGUIInput();
  }
}

void labo::app::Application::handleGUIInput() {
  sf::Event e{};
  while(window.pollEvent(e)){

  }
}
