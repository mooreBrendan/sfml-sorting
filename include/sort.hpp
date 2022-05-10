#ifndef SORT_HPP
#define SORT_HPP

#include "main.hpp"

namespace SV {

// class to show the rectangles that will be sorted
class SortRectangle : public sf::RectangleShape {
 private:
  int value;  // the value of the rectangle to be sorted
  int active;  // if the rectangle is being referenced

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

// class to display a button with text on it
class Button : public sf::RectangleShape {
 private:
  sf::Text text;  // the text on the button
  sf::Font font;  // variable to store the loaded font

 public:
  bool active;  // whether the button is being shown or not
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