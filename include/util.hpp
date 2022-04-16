#ifndef UTIL_HPP
#define UTIL_HPP

#include "main.hpp"

void initRectArray(SV::SortRectangle **, sf::Vector2u);
void initButtonArray(SV::Button *, sf::Vector2u);
void clearRectArray(SV::SortRectangle **);
int buttonPress(SV::Button *, sf::Vector2i);
void buttonArraySetActive(SV::Button *, bool);
void sortThread(SV::SortRectangle **, SV::Button *, sf::Mouse *,
                sf::RenderWindow *, sf::Vector2i *, sf::Mutex *);

void red();
void green();
void yellow();
void blue();
void magenta();
void cyan();
void white();
void reset();
void color(int);

#endif