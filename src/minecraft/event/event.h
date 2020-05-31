#ifndef LABO_EVENT_H
#define LABO_EVENT_H

namespace labo::minecraft{

class Level;

struct Event{
  virtual void handle(Level &level) = 0;
};

}

#endif //LABO_EVENT_H
