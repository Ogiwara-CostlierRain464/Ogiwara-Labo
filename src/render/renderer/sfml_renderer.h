#ifndef LABO_SFML_RENDERER_H
#define LABO_SFML_RENDERER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

namespace labo::render{
class SFMLRenderer {
public:
  void add(const sf::Drawable *drawable);
  void render(sf::RenderWindow &window);

private:
  std::vector<const sf::Drawable *> draws;
};
}

#endif //LABO_SFML_RENDERER_H
