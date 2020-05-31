#ifndef LABO_TOGGLE_KEY_H
#define LABO_TOGGLE_KEY_H

#include <SFML/Graphics.hpp>

namespace labo::app{

/**
 * オン/オフを表現するために、一定時間間隔でのボタン操作
 * を提供するトグルボタン
 */
class ToggleKey{
public:
  explicit ToggleKey(sf::Keyboard::Key key)
    : key(key)
  {}

  bool isKeyPressed(){
    if(delayTimer.getElapsedTime().asSeconds() > 0.2){
      if(sf::Keyboard::isKeyPressed(key)){
        delayTimer.restart();
        return true;
      }
    }
    return false;
  }

private:
  sf::Keyboard::Key key;
  sf::Clock delayTimer;
};

}

#endif //LABO_TOGGLE_KEY_H
