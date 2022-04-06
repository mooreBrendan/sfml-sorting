#ifndef SORT_HPP
#define SORT_HPP

#include "main.hpp"

namespace Sort {

class SortRectangle : public sf::RectangleShape {
private:
  int value;
  float position;
  bool active;

public:
  SortRectangle();
  void setValues(sf::Vector2f, sf::Vector2f);
  void update();
  void setActive(bool);
};

class Button : public sf::RectangleShape {
private:
  sf::Text text;

public:
  Button(sf::Vector2f, sf::Vector2f, sf::Text);
  bool isClicked(sf::Vector2f);
};

void quicksort(SortRectangle *, int);
void mergesort(SortRectangle *, int);
void bubblesort(SortRectangle *, int);
void insertionsort(SortRectangle *, int);
}

#endif