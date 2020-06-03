#ifndef LABO_TEXT_RENDERER_H
#define LABO_TEXT_RENDERER_H

#define GLT_IMPLEMENTATION
#include <gltext.h>
#include <string>
#include <vector>
#include <memory>

namespace labo::render{
class TextRenderer{
public:
  TextRenderer(){
    gltInit();
  }

  ~TextRenderer(){
    for(auto &ptr: texts){
      gltDeleteText(ptr);
    }
    gltTerminate();
  }

  void add(){
    auto text = gltCreateText();
    gltSetText(text, "Hello World!");
    texts.push_back(text);
  }

  void render(){
    gltBeginDraw();

    for(auto text : texts){
      gltColor(0.5f, 0.0f, 0.0f, 1.0f);
      gltDrawText2D(text, 0.0f, 0.0f, 1.0f);
    }

    gltEndDraw();
  }

private:
  std::vector<GLTtext *> texts;
};
}

#endif //LABO_TEXT_RENDERER_H
