#include "main.hpp"

// initialize an arrray of random rectangles
void initRectArray(SV::SortRectangle **arr, sf::Vector2u windowSize) {
  for (int i = 0; i < NUM_RECTS; i++) {
    // create the array
    arr[i] = new SV::SortRectangle();
  }

  scaleRectArray(arr, windowSize);
}

void scaleRectArray(SV::SortRectangle **arr, sf::Vector2u windowSize) {
  float width = (float)windowSize.x / NUM_RECTS;  // width of each subsection
  float height = windowSize.y;                    // screen height
  float rWidth = width * .95;  // width of bar with room between
  float rHeight;               // variable to temporarily store bar height
  int val;
  sf::Vector2f pos;

  // perform initialization for each rectangle
  for (int i = 0; i < NUM_RECTS; i++) {
    if (arr[i] != nullptr) {
      // get random value for the rectangle height and find width
      rHeight = ((arr[i]->getValue() * height) / 100) + 1;
      pos.x = i * width;
      pos.y = height - rHeight;
      arr[i]->setValues(sf::Vector2f(rWidth, rHeight), pos);
    }
  }
}

// initializes an array of buttons for the menu
void initButtonArray(SV::Button *arr, sf::Vector2u windowSize) {
  // get basic position values
  float width = windowSize.x * .75;
  float height = windowSize.y / NUM_BUTTONS;
  sf::Vector2f pos;
  pos.x = (windowSize.x - width) / 2;

  // initialize position and size of each button
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pos.y = height * i;
    arr[i].setSize(sf::Vector2f(width, height * .95));
    arr[i].setPosition(pos);
    arr[i].setFillColor(BUTTON_NORMAL);
    arr[i].setTextFormat();
  }
}

// deletes the rectangles that were created with new
void clearRectArray(SV::SortRectangle **arr) {
  for (int i = NUM_RECTS - 1; i >= 0; i--) {
    delete arr[i];
  }
}

// check if a button was pressed, and return it
int buttonPress(SV::Button *bArr, sf::Vector2i click) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    if (bArr[i].mouseOver(click)) {
      return i + 1;
    }
  }
  return 0;
}

// set each button as if it is shown or not
void buttonArraySetActive(SV::Button *arr, bool state) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    arr[i].active = state;
  }
}

// clears the previous set of rectangles and initializes a new set
void algPrep(SV::SortRectangle **rArr, SV::Button *bArr,
             sf::Vector2u windowSize) {
  clearRectArray(rArr);
  initRectArray(rArr, windowSize);
  buttonArraySetActive(bArr, false);
}

// thread function to handle selection of sorting algorithms
void sortThread(SV::SortRectangle **rArr, SV::Button *bArr, sf::Mouse *mouse,
                sf::RenderWindow *window, sf::Vector2i *click,
                sf::Mutex *algoMut) {
  int algorithm = 0;
  while (true) {                       // run until terminated
    buttonArraySetActive(bArr, true);  // set  buttons as shown

    // check if a button has been clicked
    algoMut->lock();
    if (click->x != 0) {
      algorithm = buttonPress(bArr, *click);
#ifdef DEBUG
      std::cout << "called: " << algorithm << std::endl;
      std::cout << "x: " << click->x << ", y: " << click->y << std::endl;
      std::cout << std::endl << std::endl << std::endl;
#endif
      click->x = 0;
      click->y = 0;
    }
    algoMut->unlock();

    // determine which algorithm has been selected
    switch (algorithm) {
      case 1:
        algPrep(rArr, bArr, window->getSize());
        SV::quicksort(rArr, NUM_RECTS);
        break;
      case 2:
        algPrep(rArr, bArr, window->getSize());
        SV::mergesort(rArr, NUM_RECTS);
        break;
      case 3:
        algPrep(rArr, bArr, window->getSize());
        SV::bubblesort(rArr, NUM_RECTS);
        break;
      case 4:
        algPrep(rArr, bArr, window->getSize());
        SV::insertionsort(rArr, NUM_RECTS);
        break;

      default:
        break;
    }
    algorithm = 0;
  }
}

void red() { std::cout << "\033[1;31m"; }
void green() { std::cout << "\033[1;32m"; }
void yellow() { std::cout << "\033[1;33m"; }
void blue() { std::cout << "\033[1;34m"; }
void magenta() { std::cout << "\033[1;35m"; }
void cyan() { std::cout << "\033[1;36m"; }
void white() { std::cout << "\033[1;37m"; }
void reset() { std::cout << "\033[0m"; }
void color(int x) { std::cout << "\033[1;" << 31 + (x % 7) << "m"; }