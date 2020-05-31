#include "sfml_renderer.h"

void labo::render::SFMLRenderer::add(const sf::Drawable *drawable) {
  draws.push_back(drawable);
}

void labo::render::SFMLRenderer::render(sf::RenderWindow &window) {
  if(draws.empty())
    return;

  draws.clear();
}
