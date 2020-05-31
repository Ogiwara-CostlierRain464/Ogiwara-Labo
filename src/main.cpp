#include "application/application.h"

using namespace labo::app;

void test(){
  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.majorVersion = 3;
  settings.minorVersion = 2;

  sf::RenderWindow window(sf::VideoMode(800, 600, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);

  //if(!gladLoadGL()) exit(-1);


  sf::Font font;
  font.loadFromFile("rs.ttf");
  sf::Text text("SFML / OpenGL demo", font);
  text.setCharacterSize(60);
  text.setFillColor(sf::Color::Red);
  text.setPosition(100,100);

  while(true){
    // Clear the screen to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    window.setActive(false);

    // Draw some text on top of our OpenGL object
    window.pushGLStates();
    window.draw(text);
    window.popGLStates();

    // Swap buffers
    window.display();
  }
}

int main(){
  test();

  Application app;
  app.mainLoop();
}