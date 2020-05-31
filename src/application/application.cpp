#include "application.h"
#include <glad/glad.h>
#include "input/toggle_key.h"
#include <SFML/Graphics.hpp>
#include "../minecraft/event/player_input_event.h"

using sf::Clock;
using sf::Time;
using labo::render::Camera;
using labo::render::CameraConfig;
using labo::minecraft::PlayerInputEvent;

namespace {
  constexpr float windowX = 1200;
  constexpr float windowY = 800;
  constexpr float fov = 90;
}

labo::app::Application::Application()
  : camera(Camera(CameraConfig{windowX, windowY, fov}))
{

  sf::ContextSettings settings{};
  settings.majorVersion = 4;
  settings.minorVersion = 1;
  settings.depthBits = 24;
  settings.stencilBits = 8;

  sf::VideoMode winMode(windowX, windowY);
  window.create(winMode, "Labo", sf::Style::Titlebar | sf::Style::Close, settings);

  if(!gladLoadGL()) exit(-1);

  window.setVerticalSyncEnabled(true);
  //window.setMouseCursorGrabbed(true);
  window.setMouseCursorVisible(false);

  glViewport(0, 0, window.getSize().x, window.getSize().y);
  glCullFace(GL_BACK);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  camera.hookPlayer(&level.getPlayer());
}

void labo::app::Application::mainLoop() {
  Clock dtTimer;

  // test to print SFML drawable
  sf::Font font;
  if(!font.loadFromFile("res/rs.ttf")){
    perror("Load font");
    exit(-1);
  }
  sf::Text text("OpenGL Demo", font);
  text.setCharacterSize(60);
  text.setFillColor(sf::Color::Red);
  text.setPosition(100,100);

  while(window.isOpen()){
    auto deltaTime = dtTimer.restart();

    handleGUIInput();

    level.update(deltaTime.asSeconds());
    camera.update();

    // render runs at here

    //renderMaster.finish(window, camera);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    window.setActive(false);

    window.pushGLStates();
    window.draw(text);
    window.popGLStates();

    window.display();

  }
}

void labo::app::Application::handleGUIInput() {

  std::vector<sf::Keyboard::Key> keys;
  handleKeyboardInput(keys);
  sf::Vector2i mouseChange;
  handleMouseInput(mouseChange);

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

void labo::app::Application::handleKeyboardInput(std::vector<sf::Keyboard::Key> &keys) {

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
}

void labo::app::Application::handleMouseInput(sf::Vector2i  &mouseMove) {
  static auto lastMousePosition = sf::Mouse::getPosition(window);
  mouseMove = sf::Mouse::getPosition() - lastMousePosition;
}
