#ifndef SORT_HPP
#define SORT_HPP

#include "main.hpp"

namespace Sort {

class SortRectangle : public sf::RectangleShape {
private:
  int value;
  int x;
  bool active;

public:
  SortRectangle(sf::Vector2f);
  void update();
  void setActive(bool);
};

void quicksort(SortRectangle *, int);
void mergesort(SortRectangle *, int);
void bubblesort(SortRectangle *, int);
void insertionsort(SortRectangle *, int);
}

#endif