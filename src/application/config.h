#ifndef LABO_CONFIG_H
#define LABO_CONFIG_H

namespace labo::app{

struct Config{
  int windowX = 1280;
  int windowY = 720;
  bool isFullScreen = false;
  int renderDistance = 16;
  int fov = 90;
};

}
#endif //LABO_CONFIG_H
