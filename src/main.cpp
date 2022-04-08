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

void initButtonArray(SV::Button *arr, sf::Vector2u windowSize) {
  float width = windowSize.x * .75;
  float height = windowSize.y / NUM_BUTTONS;
  sf::Vector2f pos;
  pos.x = (windowSize.x - width) / 2;
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pos.y = height * i;
    arr[i].setSize(sf::Vector2f(width, height * .95));
    arr[i].setPosition(pos);
    arr[i].setFillColor(BUTTON_NORMAL);
    arr[i].setTextPos();
  }
}

void clearRectArray(SV::SortRectangle **arr) {
  for (int i = NUM_RECTS - 1; i >= 0; i--) {
    delete arr[i];
  }
}

int buttonPress(SV::Button *bArr, sf::Vector2i click) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    if (bArr[i].mouseOver(click)) {
      return i + 1;
    }
  }
  return 0;
}

void buttonArraySetActive(SV::Button *arr, bool state) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    arr[i].active = state;
  }
}

void sortThread(SV::SortRectangle **rArr, SV::Button *bArr, sf::Mouse *mouse,
                sf::RenderWindow *window, sf::Vector2i *click,
                sf::Mutex *algoMut) {
  int algorithm = 0;
  while (true) {
    buttonArraySetActive(bArr, true);
    algoMut->lock();
    if (click->x != 0) {
      algorithm = buttonPress(bArr, *click);
      std::cout << "called: " << algorithm << std::endl;
      std::cout << "x: " << click->x << ", y: " << click->y << std::endl;
      click->x = 0;
      click->y = 0;
    }
    algoMut->unlock();

    switch (algorithm) {
    case 1:
      buttonArraySetActive(bArr, false);
      SV::quicksort(rArr, NUM_RECTS);
      break;
    case 2:
      buttonArraySetActive(bArr, false);
      SV::mergesort(rArr, NUM_RECTS);
      break;
    case 3:
      buttonArraySetActive(bArr, false);
      SV::bubblesort(rArr, NUM_RECTS);
      break;
    case 4:
      buttonArraySetActive(bArr, false);
      SV::insertionsort(rArr, NUM_RECTS);
      break;

    default:
      break;
    }
    algorithm = 0;
  }
}

int main() {
  std::srand(time(NULL));

  sf::Mouse mouse;
  sf::RenderWindow window(sf::VideoMode(640, 480), "Sorting Algorithms");
  sf::Mutex algoMut;

  int algorithm;
  int state = 0;
  sf::Vector2i click;

  // create an array of random rectangles
  SV::SortRectangle *rects[NUM_RECTS];
  initRectArray(rects, window.getSize());

  // array to store the buttons in the game
  SV::Button buttons[] = {SV::Button("Quick Sort"), SV::Button("Merge Sort"),
                          SV::Button("Bubble Sort"),
                          SV::Button("Insertion Sort")};
  initButtonArray(buttons, window.getSize());

  // start theread for sorting
  sf::Thread thread(std::bind(&sortThread, rects, buttons, &mouse, &window,
                              &click, &algoMut));
  thread.launch();
  while (window.isOpen()) {
    sf::Event event;
    click.x = 0;
    click.y = 0;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        thread.terminate();
        for (int i = NUM_RECTS; i >= 0; i--) {
          delete rects[i];
        }
        window.close();
      } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          algoMut.lock();
          click.x = event.mouseButton.x;
          click.y = event.mouseButton.y;
          std::cout << "CLICK x: " << click.x << ", y: " << click.y
                    << std::endl;
          algoMut.unlock();
        }
      }
    }
    window.clear();
    for (int i = 0; i < NUM_RECTS; i++) {
      rects[i]->update();
      window.draw(*(rects[i]));
    }
    for (int i = 0; i < NUM_BUTTONS; i++) {
      if (buttons[i].active) {
        buttons[i].mouseUpdate(mouse.getPosition(window));
        window.draw(buttons[i]);
        window.draw(buttons[i].getText());
      }
    }
    window.display();
  }
  return 0;
}