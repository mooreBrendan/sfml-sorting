#include "main.hpp"

using namespace SV;

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
  case 1:
    temp = sf::Color::Red;
    break;
  case 2:
    temp = sf::Color::Green;
    break;
  default:
    temp = sf::Color::White;
  }
  setFillColor(temp);
}

float SortRectangle::getPos() { return getPosition().x; }
void SortRectangle::setPos(float pos) {
  position = pos;
  sf::Vector2f temp = getPosition();
  temp.x = pos;
  setPosition(temp);
}

void SortRectangle::print() {
  float x, y;
  sf::Vector2f temp = getPosition();
  x = temp.x;
  y = temp.y;
  std::cout << "x:" << x << ",y: " << y << std::endl;
}

void SortRectangle::swap(SortRectangle *s) {
  setActive(2);
  s->setActive(2);
#ifdef DEBUG
  std::cout << "s1: ";
  print();
  std::cout << "s2: ";
  s->print();
#endif

  float temp = getPosition().x;
  setPos(s->getPos());
  s->setPos(temp);
  sf::sleep(sf::milliseconds(100));

#ifdef DEBUG
  std::cout << "s1: ";
  print();
  std::cout << "s2: ";
  s->print();
#endif
  setActive(0);
  s->setActive(0);
}

int SortRectangle::getValue() { return value; }

// sets if a rectangle is currently being accessed
void SortRectangle::setActive(int act) { active = act; }

// performs the quick sort algorithm
void SV::quicksort(SortRectangle **arr, int size) {}

// performs the merge sort algorithm
void SV::mergesort(SortRectangle **arr, int size) {}

// performs the bubble sort algorithm
void SV::bubblesort(SortRectangle **arr, int size) {}

// performs the insertion sort algorithm
void SV::insertionsort(SortRectangle **arr, int size) {
  SortRectangle *temp;
  for (int i = 1; i < size; i++) {
    for (int j = 0; j < i; j++) {
#ifdef DEBUG
      std::cout << "I: " << i << ",J: " << j << std::endl;
      std::cout << "i: ";
      arr[i]->print();
      std::cout << "j: ";
      arr[j]->print();
#endif

      arr[i]->setActive(1);
      arr[j]->setActive(1);
      if (arr[j]->getValue() > arr[i]->getValue()) {
#ifdef DEBUG
        std::cout << "swap" << std::endl;
#endif
        arr[j]->swap(arr[i]);
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      } else {

        sf::sleep(sf::milliseconds(100));
      }

#ifdef DEBUG
      std::cout << "i: ";
      arr[i]->print();
      std::cout << "j: ";
      arr[j]->print();
      std::cout << std::endl << std::endl;
#endif
      arr[j]->setActive(0);
    }
    arr[i]->setActive(0);
  }
}

Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Text txt)
    : sf::RectangleShape(size) {
  setPosition(pos);
  text = txt;
  text.setPosition(pos);
}

bool Button::isClicked(sf::Vector2f click) {
  sf::Vector2f pos = getPosition();
  sf::Vector2f size = getSize();
  if (pos.x < click.x && click.x < pos.x + size.x) {
    if (pos.y < click.y && click.y < pos.y + size.y) {
      return true;
    }
  }
  return false;
}
