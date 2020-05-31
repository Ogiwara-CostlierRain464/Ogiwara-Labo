#include "application.h"
#include "input/toggle_key.h"
#include <SFML/Graphics.hpp>
#include "../minecraft/event/player_input_event.h"

using sf::Clock;
using sf::Time;
using labo::render::Camera;
using labo::render::CameraConfig;
using labo::minecraft::PlayerInputEvent;

labo::app::Application::Application()
  : camera(Camera(CameraConfig{1200, 800, 90}))
{
  camera.hookPlayer(&level.getPlayer());
}

void labo::app::Application::mainLoop() {
  Clock dtTimer;

  while(window.isOpen()){
    auto deltaTime = dtTimer.restart();

    handleGUIInput();

    level.update(deltaTime.asSeconds());
    camera.update();

    // render runs at here

    renderMaster.finish(window, camera);

  }
}

void labo::app::Application::handleGUIInput() {
  auto keys = handleKeyboardInput();
  auto mouseChange = handleMouseInput();

  level.addEvent<PlayerInputEvent>(keys, mouseChange);

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

std::vector<sf::Keyboard::Key> &&labo::app::Application::handleKeyboardInput() {
  std::vector<sf::Keyboard::Key> keys;

  if(keyboard.isKeyDown(sf::Keyboard::W)){
    keys.push_back(sf::Keyboard::W);
  }
  if(keyboard.isKeyDown(sf::Keyboard::S)){
    keys.push_back(sf::Keyboard::S);
  }
  if(keyboard.isKeyDown(sf::Keyboard::A)){
    keys.push_back(sf::Keyboard::A);
  }
  if(keyboard.isKeyDown(sf::Keyboard::D)){
    keys.push_back(sf::Keyboard::D);
  }
  if(keyboard.isKeyDown(sf::Keyboard::Space)) {
    keys.push_back(sf::Keyboard::Space);
  }

  return std::move(keys);
}

sf::Vector2i &&labo::app::Application::handleMouseInput() {
  static auto lastMousePosition = sf::Mouse::getPosition(window);
  auto change = sf::Mouse::getPosition() - lastMousePosition;

  return std::move(change);
}
