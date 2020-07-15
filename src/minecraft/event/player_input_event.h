#ifndef LABO_PLAYER_INPUT_EVENT_H
#define LABO_PLAYER_INPUT_EVENT_H

#include "event.h"
#include "../level/level.h"
#include "../../math/ray.h"
#include "../entity/item_entity.h"
#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

using glm::cos;
using glm::sin;
using glm::radians;

namespace labo::minecraft{

/**
 * Playerからの入力時に発火するイベント
 */
class PlayerInputEvent: public Event{
public:
  PlayerInputEvent(std::vector<sf::Keyboard::Key> &keys, sf::Vector2i &mouseMove)
    : keys(std::move(keys))
    , mouseMove(std::move(mouseMove))
  {}

  /**
   * 入力に応じて位置のアップデートや視点の移動等を行う
   */
  void handle(Level &level) override {
    handleKeyboard(level);
    handleMouse(level);
  }

private:
  void handleKeyboard(Level &level){
    auto &player = level.getPlayer();

    float speed = 0.2;

    // handle keyboard
    if(std::count(keys.begin(), keys.end(), sf::Keyboard::W)){
      player.acceleration.x += -cos(radians(player.getRotation().y + 90)) * speed;
      player.acceleration.z += -sin(radians(player.getRotation().y + 90)) * speed;
    }
    if(std::count(keys.begin(), keys.end(), sf::Keyboard::S)){
      player.acceleration.x += cos(radians(player.getRotation().y + 90)) * speed;
      player.acceleration.z += sin(radians(player.getRotation().y + 90)) * speed;
    }
    if(std::count(keys.begin(), keys.end(), sf::Keyboard::A)){
      player.acceleration.x += -cos(radians(player.getRotation().y)) * speed;
      player.acceleration.z += -sin(radians(player.getRotation().y)) * speed;
    }
    if(std::count(keys.begin(), keys.end(), sf::Keyboard::D)){
      player.acceleration.x += cos(radians(player.getRotation().y)) * speed;
      player.acceleration.z += sin(radians(player.getRotation().y)) * speed;
    }
    if(std::count(keys.begin(), keys.end(), sf::Keyboard::F)){
      player.toggleFlying();
    }

    if(std::count(keys.begin(), keys.end(), sf::Keyboard::Space)){
      if(!player.isFlying()){
        if(player.isOnGround()){
          player.setOnGround(false);
          player.acceleration.y += speed * 50;
        }
      }else{
        player.acceleration.y += speed * 3;
      }
    } else if(std::count(keys.begin(), keys.end(), sf::Keyboard::LShift) && player.isFlying()){
      player.acceleration.y -= speed * 3;
    }

    if(std::count(keys.begin(), keys.end(), sf::Keyboard::Q)){
      math::Ray ray(player.getPosition(), player.getRotation());
      auto placeAt = ray.getEnd();

      auto entity = std::make_shared<ItemEntity>(
        level.getNextEntityId(),placeAt);

      level.addEntity(entity);
    }

    if(std::count(keys.begin(), keys.end(), sf::Keyboard::R)){
      math::Ray ray(player.getPosition(), player.getRotation());
      auto placeAt = ray.getEnd();

      auto entity = std::make_shared<ItemEntity>(
        level.getNextEntityId(),placeAt);

      level.addStaticEntity(entity);
    }
  }
  void handleMouse(Level &level){
    auto &player = level.getPlayer();

    static float const BOUND = 89.f;
    static float const MOUSE_SPEED = 0.4;

    player.getRotation().y += mouseMove.x * MOUSE_SPEED;
    player.getRotation().x += mouseMove.y * MOUSE_SPEED;

    if(player.getRotation().x > BOUND){
      player.getRotation().x = BOUND;
    } else if(player.getRotation().x < -BOUND){
      player.getRotation().x = -BOUND;
    }

    if(player.getRotation().y > 360){
      player.getRotation().y = 0;
    } else if(player.getRotation().y < 0){
      player.getRotation().y = 360;
    }
  }



  const std::vector<sf::Keyboard::Key> keys;
  const sf::Vector2i mouseMove;
};
}

#endif //LABO_PLAYER_INPUT_EVENT_H
