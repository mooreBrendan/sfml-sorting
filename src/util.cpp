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

// checks if array is properly sorted in increasing order
bool validateRectArray(SV::SortRectangle **arr, sf::Mutex *mut) {
  bool out = true;
  if (*arr == nullptr) {  // check array exists
    return out;
  }

  arr[0]->setActive(1, mut);
  // run through the loop and check against previous elements
  for (int i = 1; i < NUM_RECTS; i++) {
    arr[i]->setActive(1, mut);
    // check if element is not greater or equal to previous and say its wrong
    if (arr[i]->compare(arr[i - 1], mut) < 0) {
      std::cout << "out of order: i:" << i << ", val:" << arr[i]->getValue()
                << ", i-1:" << i - 1 << ", val:" << arr[i - 1]->getValue()
                << std::endl;
      out = false;
    } else {  // if in order, mark it
      arr[i - 1]->setActive(2, mut);
    }
    sf::sleep(DISPLAY_DELAY);
  }

  // show the final element as marked
  arr[NUM_RECTS - 1]->setActive(2, mut);
  return out;
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
             sf::Vector2u windowSize, sf::Mutex *mut) {
  mut->lock();
  clearRectArray(rArr);
  initRectArray(rArr, windowSize);
  buttonArraySetActive(bArr, false);
  mut->unlock();
}

// runs the algorithms
void algRun(void (*alg)(SV::SortRectangle **, int, sf::Mutex *),
            SV::SortRectangle **rArr, SV::Button *bArr,
            sf::RenderWindow *window, sf::Mutex *algoMut) {
  algPrep(rArr, bArr, window->getSize(), algoMut);
  alg(rArr, NUM_RECTS, algoMut);
  validateRectArray(rArr, algoMut);
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
        algRun(SV::quicksort, rArr, bArr, window, algoMut);
        break;
      case 2:
        algRun(SV::mergesort, rArr, bArr, window, algoMut);
        break;
      case 3:
        algRun(SV::bubblesort, rArr, bArr, window, algoMut);
        break;
      case 4:
        algRun(SV::insertionsort, rArr, bArr, window, algoMut);
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