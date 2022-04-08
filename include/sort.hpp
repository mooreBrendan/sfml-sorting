#ifndef SORT_HPP
#define SORT_HPP

#include "main.hpp"

namespace SV {

class SortRectangle : public sf::RectangleShape {
private:
  int value;
  float position;
  int active;

public:
  SortRectangle();
  void swap(SortRectangle *);
  void setValues(sf::Vector2f, sf::Vector2f);
  void update();
  void setActive(int);
  int getValue();
  float getPos();
  void setPos(float);
  void print();
};

class Button : public sf::RectangleShape {
private:
  sf::Text text;

public:
  bool active;
  Button(std::string);
  sf::Text getText();
  void setTextPos();
  bool mouseOver(sf::Vector2i);
  void mouseUpdate(sf::Vector2i);
};

void quicksort(SV::SortRectangle **, int);
void mergesort(SV::SortRectangle **, int);
void bubblesort(SV::SortRectangle **, int);
void insertionsort(SV::SortRectangle **, int);
}

#endif