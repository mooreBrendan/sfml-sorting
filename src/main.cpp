#include "main.hpp"

int stateUpdate(int color, int *state) {
  if (!(*state)) {
    color++;
    *state = color == 256 ? 1 : *state;
  } else {
    color--;
    *state = color == 0 ? 0 : *state;
  }
  return color;
}

int main() {
  int r, rs, g, gs, b, bs;
  int count;
  float elapsedTime;
  sf::RenderWindow window(sf::VideoMode(640, 480), "Hello World");
  sf::CircleShape shape(200, 6);

  r = 0;
  g = 150;
  b = 250;
  rs = gs = bs = 0;
  count = 0;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();

    if (count == 0) {
      r = stateUpdate(r, &rs);
      g = stateUpdate(g, &gs);
      b = stateUpdate(b, &bs);
    }
    count = (count + 1) % 100;

    shape.setFillColor(sf::Color(r, g, b));
    window.clear();
    window.draw(shape);
    window.display();
  }
  return 0;
}