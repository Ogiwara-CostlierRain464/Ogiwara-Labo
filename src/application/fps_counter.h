#ifndef LABO_FPS_COUNTER_H
#define LABO_FPS_COUNTER_H

#include <SFML/Graphics.hpp>
#include <iostream>

namespace labo::app{

class FPSCounter{
public:
  void show(){
    frameCount++;

    if(delayTimer.getElapsedTime().asSeconds() > 0.5){
      fps = (float) frameCount / fpsTimer.restart().asSeconds();
      frameCount = 0;
      delayTimer.restart();
      std::cout << fps << std::endl;
    }
  }

private:
  sf::Clock delayTimer;
  sf::Clock fpsTimer;
  float fps;
  int frameCount = 0;
};

}

#endif //LABO_FPS_COUNTER_H
