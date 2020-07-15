#include "application.h"
#include <glad/glad.h>
#include "input/toggle_key.h"
#include <SFML/Graphics.hpp>
#include "../minecraft/event/player_input_event.h"
#include "../minecraft/event/block_break_event.h"
#include "../render/builder/level_mesh_builder.h"
#include "../math/ray.h"
#include "../minecraft/block/block.h"

using sf::Clock;
using sf::Time;
using labo::render::Camera;
using labo::render::CameraConfig;
using labo::minecraft::PlayerInputEvent;
using labo::minecraft::BlockBreakEvent;
using labo::render::LevelMeshBuilder;
using labo::math::Ray;
using labo::minecraft::Air;
using labo::minecraft::Water;

namespace {
  constexpr float windowX = 1200;
  constexpr float windowY = 800;
  constexpr float fov = 90;
  constexpr int renderDistance = 8;
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

  window.setVerticalSyncEnabled(true);
  //window.setMouseCursorGrabbed(true);
  //window.setMouseCursorVisible(false);

  if(!gladLoadGL()) exit(-1);

  glViewport(0, 0, window.getSize().x, window.getSize().y);
  glCullFace(GL_BACK);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  camera.hookPlayer(&level.getPlayer());
}

void labo::app::Application::mainLoop() {
  Clock dtTimer;

  labo::render::RenderMaster renderMaster;
  LevelMeshBuilder levelMeshBuilder(level, renderMaster);

  while(window.isOpen()){
    auto deltaTime = dtTimer.restart();
    float timeElapsed = deltaTime.asSeconds();

    fpsCounter.show();

    handleGUIInput();

    level.update(timeElapsed);
    camera.update();

    levelMeshBuilder
    .buildAndPushToRenderer(renderDistance, camera);
    renderMaster.finish(window, camera, timeElapsed);
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

  static ToggleKey flyKey(sf::Keyboard::F);
  static ToggleKey itemPopKey(sf::Keyboard::Q);

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
  if(flyKey.isKeyPressed()){
    keys.push_back(sf::Keyboard::F);
  }
  if(keyboard.isKeyDown(sf::Keyboard::Space)) {
    keys.push_back(sf::Keyboard::Space);
  }
  if(keyboard.isKeyDown(sf::Keyboard::LShift)) {
    keys.push_back(sf::Keyboard::LShift);
  }
  if(itemPopKey.isKeyPressed()) {
    keys.push_back(sf::Keyboard::Q);
  }
}

void labo::app::Application::handleMouseInput(sf::Vector2i  &mouseMove) {
  static auto lastMousePosition = sf::Mouse::getPosition(window);
  mouseMove = sf::Mouse::getPosition() - lastMousePosition;

  lastMousePosition = sf::Mouse::getPosition();



  static sf::Clock timer;
  glm::vec3 lastPosition;

  auto &player = level.getPlayer();

  for(Ray ray(
    {player.getPosition().x,
     player.getPosition().y + labo::minecraft::Player::height,
     player.getPosition().z},player.getRotation());
     ray.getLength() < 6;
     ray.step(0.05f)){
    int x = static_cast<int>(ray.getEnd().x);
    int y = static_cast<int>(ray.getEnd().y);
    int z = static_cast<int>(ray.getEnd().z);

    auto block = level.getBlock(x, y, z);

    if(block != Air && block != Water){
      if(timer.getElapsedTime().asSeconds() > 0.2){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
          timer.restart();
          level.addEvent<BlockBreakEvent>(ray.getEnd(), &player);

          break;
        }
      }
    }

  }
}
