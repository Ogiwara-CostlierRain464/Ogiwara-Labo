#ifndef LABO_APPLICATION_H
#define LABO_APPLICATION_H
#include "../render/camera.h"
#include "../render/render_master.h"
#include "../minecraft/level/level.h"
#include "input/keyboard.h"
#include <SFML/Graphics.hpp>

namespace labo::app{

class Application {
public:
  explicit Application();

  void mainLoop();
  void handleGUIInput();

private:
  [[nodiscard]]
  std::vector<sf::Keyboard::Key> &&handleKeyboardInput();
  [[nodiscard]]
  sf::Vector2i &&handleMouseInput();

  labo::render::Camera camera;
  labo::render::RenderMaster renderMaster;
  sf::RenderWindow window;
  Keyboard keyboard;

  labo::minecraft::Level level;
};

}

#endif //LABO_APPLICATION_H
