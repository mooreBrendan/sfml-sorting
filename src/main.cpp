#include "main.hpp"

void initRectArray(Sort::SortRectangle *arr, sf::Vector2u windowSize) {
  // initialize an arrray of random rectangles
  float width = windowSize.x / NUM_RECTS;
  float height = windowSize.y;
  float rWidth = width * .95;
  float rHeight;
  sf::Vector2f pos;
  for (int i = 0; i < NUM_RECTS; i++) {
    rHeight = (((rand() % 100) * height) / 100) + 1;
    pos.x = i * width;
    pos.y = height - rHeight;
    arr[i].setValues(sf::Vector2f(rWidth, rHeight), pos);
  }
}

int main() {
  float elapsedTime;
  int state;
  sf::Mouse mouse;
  std::srand(time(NULL));
  sf::RenderWindow window(sf::VideoMode(640, 480), "Sorting Algorithms");

  // create an array of random rectangles
  Sort::SortRectangle arr[NUM_RECTS];

  initRectArray(arr, window.getSize());
  state = 1;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();

    window.clear();
    for (int i = 0; i < NUM_RECTS; i++) {
      arr[i].update();
      window.draw(arr[i]);
    }
    window.display();
  }
  return 0;
}