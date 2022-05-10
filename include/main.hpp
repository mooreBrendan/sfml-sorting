#ifndef MAIN_HPP
#define MAIN_HPP

// main function defined constants
#define DISPLAY_DELAY sf::milliseconds(100)
#define NUM_RECTS 10
#define NUM_BUTTONS 4

// button defined constants
#define BUTTON_NORMAL sf::Color(127, 127, 127, 255)
#define BUTTON_HOVER sf::Color(100, 100, 100, 200)
#define FONT_SIZE 30

// window minimum size
#define MIN_X_SIZE 360
#define MIN_Y_SIZE 240

// necessary includes
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "sort.hpp"
#include "util.hpp"

#endif