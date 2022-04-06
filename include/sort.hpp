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
  void setValues(sf::Vector2f, float);
  void update();
  void setActive(bool);
};

void quicksort(SortRectangle *, int);
void mergesort(SortRectangle *, int);
void bubblesort(SortRectangle *, int);
void insertionsort(SortRectangle *, int);
}

#endif