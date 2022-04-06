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

  // create an array of random rectangles
  Sort::SortRectangle arr[NUM_RECTS];

  // initialize an arrray of random rectangles
  float rWidth = (window.getSize().x / NUM_RECTS) * .95;
  float height = window.getSize().y;
  float rHeight;
  for (int i = 0; i < NUM_RECTS; i++) {
    rHeight = ((rand() % 100) * height) / 100;
    arr[i].setValues(sf::Vector2f(rWidth, rHeight));
  }

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