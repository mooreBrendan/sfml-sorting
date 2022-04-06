#include "main.hpp"

using namespace Sort;

SortRectangle::SortRectangle() : sf::RectangleShape(sf::Vector2f(0, 0)) {}

// initializes the values of the rectangle
void SortRectangle::setValues(sf::Vector2f val, sf::Vector2f pos) {
  setSize(val);
  value = val.y;
  active = false;
  position = pos.x;
  sf::Vector2f temp(pos);
  setPosition(temp);
}

// updates the color of the rectangle depending of if its active
void SortRectangle::update() {
  sf::Color temp = active ? sf::Color::Red : sf::Color::Blue;
  setFillColor(temp);
}

// sets if a rectangle is currently being accessed
void SortRectangle::setActive(bool act) { active = act; }

// performs the quick sort algorithm
void quicksort(SortRectangle *arr, int size) {}

// performs the merge sort algorithm
void mergesort(SortRectangle *arr, int size) {}

// performs the bubble sort algorithm
void bubblesort(SortRectangle *arr, int size) {}

// performs the insertion sort algorithm
void insertionsort(SortRectangle *arr, int size) {}

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
