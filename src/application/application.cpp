#include "application.h"
#include "input/toggle_key.h"
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

    handleGUIInput();

    // Play STate
    camera.update();

    renderMaster.finish(window, camera);

  }
}

void labo::app::Application::handleGUIInput() {
  // fire event to move player,
  // or move camera

  // keyboard, mouse, and window event
  handleKeyboardInput();
  handleMouseInput();

  sf::Event e{};
  while(window.pollEvent(e)){
    keyboard.update(e);
    switch(e.type){
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        switch(e.key.code){
          case sf::Keyboard::Escape:
            window.close();
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }
}

void labo::app::Application::handleKeyboardInput() {
  if(keyboard.isKeyDown(sf::Keyboard::W)){

  }
  if(keyboard.isKeyDown(sf::Keyboard::S)){

  }
  if(keyboard.isKeyDown(sf::Keyboard::A)){

  }
  if(keyboard.isKeyDown(sf::Keyboard::D)){

  }
  if(keyboard.isKeyDown(sf::Keyboard::Space)) {

  }

  // fire event
}

void labo::app::Application::handleMouseInput() {
  static float const BOUND = 89.f;
  static float const MOUSE_SPEED = 0.4;
  static auto lastMousePosition = sf::Mouse::getPosition(window);
  auto change = sf::Mouse::getPosition() - lastMousePosition;

  // move player according to this

}
