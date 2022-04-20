#include "main.hpp"

using namespace SV;

/*****************************************************************************
 ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄
▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌
▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀  ▀▀▀▀█░█▀▀▀▀
▐░▌       ▐░▌▐░▌          ▐░▌               ▐░▌
▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░▌               ▐░▌
▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌               ▐░▌
▐░█▀▀▀▀█░█▀▀ ▐░█▀▀▀▀▀▀▀▀▀ ▐░▌               ▐░▌
▐░▌     ▐░▌  ▐░▌          ▐░▌               ▐░▌
▐░▌      ▐░▌ ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄      ▐░▌
▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌     ▐░▌
 ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀       ▀
*****************************************************************************/

// class to represent a bar in a sorting algorithm demonstration
SortRectangle::SortRectangle() : sf::RectangleShape(sf::Vector2f(0, 0)) {
  value = rand() % 100;
}

// initializes the values of the rectangle
void SortRectangle::setValues(sf::Vector2f size, sf::Vector2f pos) {
  setSize(size);
  active = 0;
  position = pos.x;
  sf::Vector2f temp(pos);
  setPosition(temp);
}

// updates the color of the rectangle depending of if its active
void SortRectangle::update() {
  sf::Color temp;
  switch (active) {
    case 1:  // checking
      temp = sf::Color::Red;
      break;
    case 2:  // swapping
      temp = sf::Color::Green;
      break;
    default:  // not being referenced
      temp = sf::Color::White;
  }
  setFillColor(temp);
}

// returns the x position of the rectangle
float SortRectangle::getPos() { return getPosition().x; }

// sets the position of the rectangle
void SortRectangle::setPos(float pos) {
  position = pos;
  sf::Vector2f temp = getPosition();
  temp.x = pos;
  setPosition(temp);
}

// prints the rectangle's x and y position for debugging
void SortRectangle::print() {
  float x, y;
  sf::Vector2f temp = getPosition();
  x = temp.x;
  y = temp.y;
  std::cout << "x:" << x << ",y: " << y << std::endl;
}

void SortRectangle::swap(SortRectangle *s, sf::Mutex *mut) {
  // show the rectangles as being swapped
  setActive(2, mut);
  s->setActive(2, mut);
#ifdef SWAP_DEBUG
  std::cout << "s1: ";
  print();
  std::cout << "s2: ";
  s->print();
#endif

  mut->lock();
  // swap their positions on screen
  float temp = getPosition().x;
  setPos(s->getPos());
  s->setPos(temp);
  mut->unlock();
  sf::sleep(DISPLAY_DELAY);

#ifdef SWAP_DEBUG
  std::cout << "s1: ";
  print();
  std::cout << "s2: ";
  s->print();
#endif
  // set the rectangles as not being swapped
  setActive(0, mut);
  s->setActive(0, mut);
}

// thread safe compare two rectangles (-1:less,0:equal,1:greater)
int SortRectangle::compare(SortRectangle *other, sf::Mutex *mut) {
  int out = 0;
  mut->lock();
  if (value < other->getValue()) {
    out = -1;
  } else if (value == other->getValue()) {
    out = 0;
  } else {
    out = 1;
  }

  mut->unlock();
  return out;
}

int SortRectangle::getValue() { return value; }

// sets if a rectangle is currently being accessed
void SortRectangle::setActive(int act, sf::Mutex *mut) {
  mut->lock();
  active = act;
  mut->unlock();
}

/*****************************************************************************
 ▄▄▄▄▄▄▄▄▄▄▄  ▄            ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄
▐░░░░░░░░░░░▌▐░▌          ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌
▐░█▀▀▀▀▀▀▀█░▌▐░▌          ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌
▐░▌       ▐░▌▐░▌          ▐░▌          ▐░▌       ▐░▌▐░▌       ▐░▌
▐░█▄▄▄▄▄▄▄█░▌▐░▌          ▐░▌ ▄▄▄▄▄▄▄▄ ▐░▌       ▐░▌▐░█▄▄▄▄▄▄▄█░▌
▐░░░░░░░░░░░▌▐░▌          ▐░▌▐░░░░░░░░▌▐░▌       ▐░▌▐░░░░░░░░░░░▌
▐░█▀▀▀▀▀▀▀█░▌▐░▌          ▐░▌ ▀▀▀▀▀▀█░▌▐░▌       ▐░▌▐░█▀▀▀▀█░█▀▀
▐░▌       ▐░▌▐░▌          ▐░▌       ▐░▌▐░▌       ▐░▌▐░▌     ▐░▌
▐░▌       ▐░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌▐░▌      ▐░▌  ▄
▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌▐░▌
 ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀  ▀
*****************************************************************************/

namespace SV {

// swaps the memory addresses of two rectangles
void swap(SortRectangle **a, SortRectangle **b, sf::Mutex *mut) {
  (*a)->swap(*b, mut);
  mut->lock();
  SortRectangle *temp = *a;
  *a = *b;
  *b = temp;
  mut->unlock();
}

int findMid(SortRectangle **arr, int a, int b, int c) {
#ifdef DEBUG
  std::cout << "partitioning: ";
  std::cout << "a: " << a << ", a-val: " << arr[a]->getValue() << ", ";
  std::cout << "b: " << b << ", b-val: " << arr[b]->getValue() << ", ";
  std::cout << "c: " << c << ", c-val: " << arr[c]->getValue() << std::endl;
#endif

  // get temporary values (only care about signs)
  int tmp1 = arr[a]->getValue() > arr[b]->getValue();
  int tmp2 = arr[b]->getValue() > arr[c]->getValue();
  int tmp3 = arr[a]->getValue() > arr[c]->getValue();

  if (tmp1 == tmp2) {  // a>b>c || c>=b>=a
    return b;
  } else if (tmp1 == tmp3) {  // a>b & b>c not same sign, so a>c>b || b>=c>=a
    return c;
  } else {  // only other option
    return a;
  }
}

int partition(SortRectangle **arr, int start, int size, sf::Mutex *algoMut) {
  int pivot = findMid(arr, start, start + (size / 2), start + size - 1);
  int pValue = arr[pivot]->getValue();
  int partionIndex = start;
#ifdef DEBUG
  yellow();
  std::cout << "start partition ";
  std::cout << "start: " << start << ", size: " << size;
  std::cout << ", pivot: " << pivot << ", pval: " << pValue << std::endl;
  reset();
#endif

  for (int i = start; i < start + size; i++) {  // for each
    // if less than pivot, swap to left and increase partition
    arr[i]->setActive(1, algoMut);
    algoMut->lock();
    if (arr[i]->getValue() < pValue) {
      algoMut->unlock();
      if (i != partionIndex) {  // if already in position
#ifdef DEBUG
        green();
        std::cout << "swapping: i: " << i << ", pIndex: " << partionIndex
                  << std::endl;
        reset();
#endif
        swap(&(arr[i]), &(arr[partionIndex]), algoMut);
        if (partionIndex == pivot) {
          pivot = i;
        }
      } else {
        sf::sleep(DISPLAY_DELAY);
      }

      partionIndex++;
    } else {
      algoMut->unlock();
      sf::sleep(DISPLAY_DELAY);
    }
    arr[i]->setActive(0, algoMut);
  }
  swap(&(arr[partionIndex]), &(arr[pivot]), algoMut);
#ifdef DEBUG
  yellow();
  std::cout << "done partion: start: " << start << ", size: " << size;
  std::cout << ": partition index: " << partionIndex << std::endl;
  reset();
#endif
  return partionIndex;
}

void quicksortRecursive(SortRectangle **arr, int start, int size,
                        sf::Mutex *algoMut) {
#ifdef DEBUG
  cyan();
  std::cout << "recurse-start index: " << start;
  std::cout << ",size: " << size << std::endl;
  reset();
#endif
  if (size > 1) {
    int part = partition(arr, start, size, algoMut);
    quicksortRecursive(arr, start, part - start, algoMut);
    quicksortRecursive(arr, part + 1, (size + start) - part - 1, algoMut);
  }
#ifdef DEBUG
  cyan();
  std::cout << "recurse-stop index: " << start;
  std::cout << ",size: " << size << std::endl;
  reset();
#endif
}

// performs the quick sort algorithm
void quicksort(SortRectangle **arr, int size, sf::Mutex *algoMut) {
  quicksortRecursive(arr, 0, size, algoMut);
}

void mergesortRecursive(SortRectangle **a, int index, int size,
                        sf::Mutex *algoMut) {
#ifdef DEBUG
  std::cout << "index: " << index << ", ";
  std::cout << "size: " << size << ", n/2: " << size / 2 << std::endl;
#endif

  // check for base cases
  if (size == 1) {
    a[index]->setActive(1, algoMut);
    sf::sleep(DISPLAY_DELAY);
    a[index]->setActive(0, algoMut);
    return;
  } else if (size == 0) {
    return;
  }

  int half = size / 2;
// sort halves
#ifdef DEBUG
  std::cout << "index: " << index << ", ";
  std::cout << "splitting size: " << size << std::endl;
#endif
  SV::mergesortRecursive(a, index, half, algoMut);
  SV::mergesortRecursive(a, index + half, size - half, algoMut);
#ifdef DEBUG
  std::cout << "index: " << index << ", ";
  std::cout << "done splitting size: " << size << std::endl << std::endl;
  std::cout << "merging size: " << size << std::endl;
#endif

  // merge halves
  int l, r;
  int mid = index + half;
  for (l = index; l < index + half; l++) {
    a[l]->setActive(1, algoMut);
    a[mid]->setActive(1, algoMut);
    if (a[l]->compare(a[mid], algoMut) > 0) {
      swap(&(a[l]), &(a[mid]), algoMut);
      r = mid;
      while (r + 1 < index + size && a[r]->compare(a[r + 1], algoMut) > 0) {
        swap(&(a[r]), &(a[r + 1]), algoMut);
        r++;
        sf::sleep(DISPLAY_DELAY);
      }
    } else {
      sf::sleep(DISPLAY_DELAY);
    }
    a[l]->setActive(0, algoMut);
    a[mid]->setActive(0, algoMut);
  }
}

// performs the merge sort algorithm
void mergesort(SortRectangle **arr, int size, sf::Mutex *algoMut) {
  SV::mergesortRecursive(arr, 0, size, algoMut);
}

// performs the bubble sort algorithm
void bubblesort(SortRectangle **arr, int size, sf::Mutex *algoMut) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - 1 - i; j++) {
      // mark rectangles as being referenced
      arr[j]->setActive(1, algoMut);
      arr[j + 1]->setActive(1, algoMut);
      if (arr[j]->compare(arr[j + 1], algoMut) > 0) {
        swap(&(arr[j]), &(arr[j + 1]), algoMut);
      } else {
        sf::sleep(DISPLAY_DELAY);
      }
      arr[j]->setActive(0, algoMut);
    }
    arr[size - 1 - i]->setActive(0, algoMut);
  }
}

// performs the insertion sort algorithm
void insertionsort(SortRectangle **arr, int size, sf::Mutex *algoMut) {
  SortRectangle *temp;
  for (int i = 1; i < size; i++) {  // new insertion
    for (int j = 0; j < i; j++) {   // find where to insert
#ifdef DEBUG
      std::cout << "I: " << i << ",J: " << j << std::endl;
      std::cout << "i: ";
      arr[i]->print();
      std::cout << "j: ";
      arr[j]->print();
#endif

      // mark rectangles as being referenced
      arr[i]->setActive(1, algoMut);
      arr[j]->setActive(1, algoMut);

      // swap if necessary
      if (arr[j]->compare(arr[i], algoMut) > 0) {
#ifdef DEBUG
        std::cout << "swap" << std::endl;
#endif
        swap(&(arr[j]), &(arr[i]), algoMut);
      } else {
        sf::sleep(DISPLAY_DELAY);
      }

#ifdef DEBUG
      std::cout << "i: ";
      arr[i]->print();
      std::cout << "j: ";
      arr[j]->print();
      std::cout << std::endl << std::endl;
#endif
      // un mark the rectangle
      arr[j]->setActive(0, algoMut);
    }
    arr[i]->setActive(0, algoMut);
  }
}
}

/*****************************************************************************
 ▄▄▄▄▄▄▄▄▄▄   ▄         ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄        ▄
▐░░░░░░░░░░▌ ▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░▌      ▐░▌
▐░█▀▀▀▀▀▀▀█░▌▐░▌       ▐░▌ ▀▀▀▀█░█▀▀▀▀  ▀▀▀▀█░█▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌▐░▌░▌     ▐░▌
▐░▌       ▐░▌▐░▌       ▐░▌     ▐░▌          ▐░▌     ▐░▌       ▐░▌▐░▌▐░▌    ▐░▌
▐░█▄▄▄▄▄▄▄█░▌▐░▌       ▐░▌     ▐░▌          ▐░▌     ▐░▌       ▐░▌▐░▌ ▐░▌   ▐░▌
▐░░░░░░░░░░▌ ▐░▌       ▐░▌     ▐░▌          ▐░▌     ▐░▌       ▐░▌▐░▌  ▐░▌  ▐░▌
▐░█▀▀▀▀▀▀▀█░▌▐░▌       ▐░▌     ▐░▌          ▐░▌     ▐░▌       ▐░▌▐░▌   ▐░▌ ▐░▌
▐░▌       ▐░▌▐░▌       ▐░▌     ▐░▌          ▐░▌     ▐░▌       ▐░▌▐░▌    ▐░▌▐░▌
▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌     ▐░▌          ▐░▌     ▐░█▄▄▄▄▄▄▄█░▌▐░▌     ▐░▐░▌
▐░░░░░░░░░░▌ ▐░░░░░░░░░░░▌     ▐░▌          ▐░▌     ▐░░░░░░░░░░░▌▐░▌      ▐░░▌
 ▀▀▀▀▀▀▀▀▀▀   ▀▀▀▀▀▀▀▀▀▀▀       ▀            ▀       ▀▀▀▀▀▀▀▀▀▀▀  ▀        ▀▀
*****************************************************************************/
// class to handle a button
Button::Button(std::string txt) : sf::RectangleShape(sf::Vector2f(0, 0)) {
  if (!font.loadFromFile("Roboto-Regular.ttf")) {
    std::cout << "could not find font file\n" << std::endl;
    throw 20;
  }
  text.setFont(font);
  text.setString(txt);
  text.setPosition(getPosition());
  text.setFillColor(sf::Color::Black);
  text.setCharacterSize(FONT_SIZE);
  active = false;
}

// sets text formating options
void Button::setTextFormat() {
  // move text to the center of the button
  text.setPosition(getPosition());
#ifdef DEBUG
  std::cout << text.getString().toAnsiString() << std::endl;
  sf::Vector2f disp = text.getPosition();
  std::cout << "text: x: " << disp.x << ", y: " << disp.y << std::endl;
#endif

  sf::Vector2f temp = getSize();
  sf::FloatRect textBox = text.getLocalBounds();
  temp.x = (temp.x / 2) - (textBox.width / 2);
  temp.y = (temp.y / 2) - (textBox.height / 2);
  text.move(temp);

#ifdef DEBUG
  disp = text.getPosition();
  std::cout << "text: x: " << disp.x << ", y: " << disp.y << std::endl;
#endif
}

// returns the text element (for rendering)
sf::Text *Button::getText() { return &text; }

// determines if the mouse is over the button or not
bool Button::mouseOver(sf::Vector2i mousePos) {
  sf::Vector2f pos = getPosition();
  sf::Vector2f size = getSize();
  if (pos.x < mousePos.x && mousePos.x < pos.x + size.x) {    // check x inside
    if (pos.y < mousePos.y && mousePos.y < pos.y + size.y) {  // check y inside
      return true;
    }
  }
  return false;
}

// changes color if the button is currently being hovered over or not
void Button::mouseUpdate(sf::Vector2i mousePos) {
  sf::Color temp = mouseOver(mousePos) ? BUTTON_HOVER : BUTTON_NORMAL;
  setFillColor(temp);
}
