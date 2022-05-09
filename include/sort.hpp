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
  int compare(SortRectangle *, sf::Mutex *);
  void setValues(sf::Vector2f, sf::Vector2f);
  void update();
  void setActive(int, sf::Mutex *);
  int getValue();
  float getPos();
  void setPos(float);
  void print();
};

class Button : public sf::RectangleShape {
 private:
  sf::Text text;
  sf::Font font;

 public:
  bool active;
  Button(std::string);
  sf::Text *getText();
  void setTextFormat();
  bool mouseOver(sf::Vector2i);
  void mouseUpdate(sf::Vector2i);
};

// sort algorithms
void quicksort(SV::SortRectangle **, int, sf::Mutex *);
void mergesort(SV::SortRectangle **, int, sf::Mutex *);
void bubblesort(SV::SortRectangle **, int, sf::Mutex *);
void insertionsort(SV::SortRectangle **, int, sf::Mutex *);
}

#endif