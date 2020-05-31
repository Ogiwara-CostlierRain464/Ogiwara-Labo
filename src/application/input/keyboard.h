#ifndef LABO_KEYBOARD_H
#define LABO_KEYBOARD_H

#include <SFML/Graphics.hpp>
#include <array>

namespace labo::app{

/**
 * キーボードを表す。各キーのオン/オフ状態を管理する
 */
class Keyboard{
public:
  Keyboard(){
    std::fill(keys.begin(), keys.end(), false);
  }

  void update(sf::Event e){
    recentlyReleased = sf::Keyboard::KeyCount;
    switch(e.type){
      case sf::Event::KeyReleased:
        keys[e.key.code] = false;
        break;

      case sf::Event::KeyPressed:
        recentlyReleased = e.key.code;
        keys[e.key.code] = true;
        break;

      default:
        break;
    }
  }

  [[nodiscard]]
  bool isKeyDown(sf::Keyboard::Key key) const {
    return keys[key];
  }

  [[nodiscard]]
  bool keyReleased(sf::Keyboard::Key key) const{
    return recentlyReleased == key;
  }

private:
  std::array<bool, sf::Keyboard::KeyCount> keys{};
  sf::Keyboard::Key recentlyReleased;
};
}

#endif //LABO_KEYBOARD_H
