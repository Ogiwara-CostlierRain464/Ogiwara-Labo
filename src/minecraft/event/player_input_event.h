#ifndef LABO_PLAYER_INPUT_EVENT_H
#define LABO_PLAYER_INPUT_EVENT_H

#include "event.h"
#include "../level/level.h"
#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

using glm::cos;
using glm::sin;
using glm::radians;

namespace labo::minecraft{

class PlayerInputEvent: public Event{
public:
  PlayerInputEvent(std::vector<sf::Keyboard::Key> &keys, sf::Vector2i &mouseMove)
    : keys(std::move(keys))
    , mouseMove(std::move(mouseMove))
  {
    // NOTE: manage keys as bit mask is good idea.
  }

  void handle(Level &level) override {
    // Handle input form player, like WASD, digging
    // キーボードの入力とマウスの動きをコンストラクターにし、それをPlayer objectに反映
    auto &player = level.getPlayer();

    float speed = 0.2;

    // handle keyboard
    if(std::count(keys.begin(), keys.end(), sf::Keyboard::W)){
      player.acceleration.x += -cos(radians(player.rotation.y + 90)) * speed;
      player.acceleration.z += -sin(radians(player.rotation.y + 90)) * speed;
    }
    if(std::count(keys.begin(), keys.end(), sf::Keyboard::S)){
      player.acceleration.x += cos(radians(player.rotation.y + 90)) * speed;
      player.acceleration.z += sin(radians(player.rotation.y + 90)) * speed;
    }
    if(std::count(keys.begin(), keys.end(), sf::Keyboard::A)){
      player.acceleration.x += -cos(radians(player.rotation.y)) * speed;
      player.acceleration.z += -sin(radians(player.rotation.y)) * speed;
    }
    if(std::count(keys.begin(), keys.end(), sf::Keyboard::D)){
      player.acceleration.x += cos(radians(player.rotation.y)) * speed;
      player.acceleration.z += sin(radians(player.rotation.y)) * speed;
    }
    if(std::count(keys.begin(), keys.end(), sf::Keyboard::Space)){
      player.acceleration.y += speed * 3;
    }

    //handle mouse
    static float const BOUND = 89.f;
    static float const MOUSE_SPEED = 0.4;

    player.rotation.y += mouseMove.x * MOUSE_SPEED;
    player.rotation.x += mouseMove.y * MOUSE_SPEED;

    if(player.rotation.x > BOUND){
      player.rotation.x = BOUND;
    } else if(player.rotation.x < -BOUND){
      player.rotation.x = -BOUND;
    }

    if(player.rotation.y > 360){
      player.rotation.y = 0;
    } else if(player.rotation.y < 0){
      player.rotation.y = 360;
    }
  }

private:
  const std::vector<sf::Keyboard::Key> keys;
  const sf::Vector2i mouseMove;
};
}

#endif //LABO_PLAYER_INPUT_EVENT_H
