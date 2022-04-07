#include "main.hpp"

// initialize an arrray of random rectangles
void initRectArray(SV::SortRectangle **arr, sf::Vector2u windowSize) {
  float width = windowSize.x / NUM_RECTS;
  float height = windowSize.y;
  float rWidth = width * .95;
  float rHeight;
  sf::Vector2f pos;
  for (int i = 0; i < NUM_RECTS; i++) {
    rHeight = (((rand() % 100) * height) / 100) + 1;
    pos.x = i * width;
    pos.y = height - rHeight;
    arr[i] = new SV::SortRectangle();
    arr[i]->setValues(sf::Vector2f(rWidth, rHeight), pos);
  }
}

void clearRectArray(SV::SortRectangle **arr) {
  for (int i = NUM_RECTS - 1; i >= 0; i--) {
    delete arr[i];
  }
}

int buttonPress(sf::Vector2i click) {
  // TODO: check which button was pressed and return correct value
  return 1;
}

void sortThread(SV::SortRectangle **arr) {
  sf::Mouse mouse;
  int algorithm = 0;
  int count = 0;
  while (count != 1) {
    if (mouse.isButtonPressed(sf::Mouse::Left))
      algorithm = buttonPress(mouse.getPosition());

    switch (algorithm) {
    case 1:
      SV::insertionsort(arr, NUM_RECTS);
      std::cout << "done: " << count << std::endl;
      count++;
      break;
    case 2:
      SV::bubblesort(arr, NUM_RECTS);
      break;
    case 3:
      SV::mergesort(arr, NUM_RECTS);
      break;
    case 4:
      SV::quicksort(arr, NUM_RECTS);
      break;

    default:
      break;
    }
    algorithm = 0;
  }
}

int main() {
  float elapsedTime;
  std::srand(time(NULL));
  sf::RenderWindow window(sf::VideoMode(640, 480), "Sorting Algorithms");

  // create an array of random rectangles
  SV::SortRectangle *arr[NUM_RECTS];

  initRectArray(arr, window.getSize());

  sf::Thread thread(&sortThread, arr);
  thread.launch();
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        thread.terminate();
      }
    }

    window.clear();
    for (int i = 0; i < NUM_RECTS; i++) {
      arr[i]->update();
      window.draw(*(arr[i]));
    }
    window.display();
  }
  return 0;
}