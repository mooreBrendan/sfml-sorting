#include "main.hpp"

using namespace Sort;

// class to handle each rectangle for sorting
SortRectangle::SortRectangle(sf::Vector2f val) : sf::RectangleShape(val) {
  value = val.y;
  active = false;
  x = val.x;
}

// updates the color of the rectangle depending of if its active
void SortRectangle::update() {
  if (active) {
    setFillColor(sf::Color::Red);
  } else {
    setFillColor(sf::Color::Blue);
  }
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