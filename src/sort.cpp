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
SortRectangle::SortRectangle() : sf::RectangleShape(sf::Vector2f(0, 0)) {}

// initializes the values of the rectangle
void SortRectangle::setValues(sf::Vector2f val, sf::Vector2f pos) {
  setSize(val);
  value = val.y;
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

void SortRectangle::swap(SortRectangle *s) {
  // show the rectangles as being swapped
  setActive(2);
  s->setActive(2);
#ifdef DEBUG
  std::cout << "s1: ";
  print();
  std::cout << "s2: ";
  s->print();
#endif

  // swap their positions on screen
  float temp = getPosition().x;
  setPos(s->getPos());
  s->setPos(temp);
  sf::sleep(DISPLAY_DELAY);

#ifdef DEBUG
  std::cout << "s1: ";
  print();
  std::cout << "s2: ";
  s->print();
#endif
  // set the rectangles as not being swapped
  setActive(0);
  s->setActive(0);
}

int SortRectangle::getValue() { return value; }

// sets if a rectangle is currently being accessed
void SortRectangle::setActive(int act) { active = act; }

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

// performs the quick sort algorithm
void SV::quicksort(SortRectangle **arr, int size) {}

// performs the merge sort algorithm
void SV::mergesort(SortRectangle **arr, int size) {}

// performs the bubble sort algorithm
void SV::bubblesort(SortRectangle **arr, int size) {
  SortRectangle *temp;
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - 1; j++) {  // mark rectangles as being referenced
      arr[j]->setActive(1);
      arr[j + 1]->setActive(1);
      if (arr[j]->getValue() > arr[j + 1]->getValue()) {
        arr[j]->swap(arr[j + 1]);
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      } else {
        sf::sleep(DISPLAY_DELAY);
      }
      arr[j]->setActive(0);
    }
    arr[size - 1]->setActive(0);
  }
}

// performs the insertion sort algorithm
void SV::insertionsort(SortRectangle **arr, int size) {
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
      arr[i]->setActive(1);
      arr[j]->setActive(1);

      // swap if necessary
      if (arr[j]->getValue() > arr[i]->getValue()) {
#ifdef DEBUG
        std::cout << "swap" << std::endl;
#endif
        arr[j]->swap(arr[i]);
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
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
      arr[j]->setActive(0);
    }
    arr[i]->setActive(0);
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
