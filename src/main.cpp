#include "main.hpp"

// initialize an arrray of random rectangles
void initRectArray(SV::SortRectangle **arr, sf::Vector2u windowSize) {
  // get basic size information
  float width = windowSize.x / NUM_RECTS;  // width of each subsection
  float height = windowSize.y;             // screen height
  float rWidth = width * .95;              // width of bar with room between
  float rHeight;  // variable to temporarily store bar height
  sf::Vector2f pos;

  // perform initialization for each rectangle
  for (int i = 0; i < NUM_RECTS; i++) {
    // get random value for the rectangle height and find widht
    rHeight = (((rand() % 100) * height) / 100) + 1;
    pos.x = i * width;
    pos.y = height - rHeight;

    // create rectangle and store values
    arr[i] = new SV::SortRectangle();
    arr[i]->setValues(sf::Vector2f(rWidth, rHeight), pos);
  }
}

// initializes an array of buttons for the menu
void initButtonArray(SV::Button *arr, sf::Vector2u windowSize) {
  // get basic position values
  float width = windowSize.x * .75;
  float height = windowSize.y / NUM_BUTTONS;
  sf::Vector2f pos;
  pos.x = (windowSize.x - width) / 2;

  // initialize position and size of each button
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pos.y = height * i;
    arr[i].setSize(sf::Vector2f(width, height * .95));
    arr[i].setPosition(pos);
    arr[i].setFillColor(BUTTON_NORMAL);
    arr[i].setTextFormat();
  }
}

// deletes the rectangles that were created with new
void clearRectArray(SV::SortRectangle **arr) {
  for (int i = NUM_RECTS - 1; i >= 0; i--) {
    delete arr[i];
  }
}

// check if a button was pressed, and return it
int buttonPress(SV::Button *bArr, sf::Vector2i click) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    if (bArr[i].mouseOver(click)) {
      return i + 1;
    }
  }
  return 0;
}

// set each button as if it is shown or not
void buttonArraySetActive(SV::Button *arr, bool state) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    arr[i].active = state;
  }
}

// thread function to handle selection of sorting algorithms
void sortThread(SV::SortRectangle **rArr, SV::Button *bArr, sf::Mouse *mouse,
                sf::RenderWindow *window, sf::Vector2i *click,
                sf::Mutex *algoMut) {
  int algorithm = 0;
  while (true) {                       // run until terminated
    buttonArraySetActive(bArr, true);  // set  buttons as shown

    // check if a button has been clicked
    algoMut->lock();
    if (click->x != 0) {
      algorithm = buttonPress(bArr, *click);
#ifdef DEBUG
      std::cout << "called: " << algorithm << std::endl;
      std::cout << "x: " << click->x << ", y: " << click->y << std::endl;
      std::cout << std::endl << std::endl << std::endl;
#endif
      click->x = 0;
      click->y = 0;
    }
    algoMut->unlock();

    // determine which algorithm has been selected
    switch (algorithm) {
      case 1:
        buttonArraySetActive(bArr, false);
        SV::quicksort(rArr, NUM_RECTS);
        break;
      case 2:
        buttonArraySetActive(bArr, false);
        SV::mergesort(rArr, NUM_RECTS);
        break;
      case 3:
        buttonArraySetActive(bArr, false);
        SV::bubblesort(rArr, NUM_RECTS);
        break;
      case 4:
        buttonArraySetActive(bArr, false);
        SV::insertionsort(rArr, NUM_RECTS);
        break;

      default:
        break;
    }
    algorithm = 0;
  }
}

/*****************************************************************************
 ▄▄       ▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄        ▄
▐░░▌     ▐░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░▌      ▐░▌
▐░▌░▌   ▐░▐░▌▐░█▀▀▀▀▀▀▀█░▌ ▀▀▀▀█░█▀▀▀▀ ▐░▌░▌     ▐░▌
▐░▌▐░▌ ▐░▌▐░▌▐░▌       ▐░▌     ▐░▌     ▐░▌▐░▌    ▐░▌
▐░▌ ▐░▐░▌ ▐░▌▐░█▄▄▄▄▄▄▄█░▌     ▐░▌     ▐░▌ ▐░▌   ▐░▌
▐░▌  ▐░▌  ▐░▌▐░░░░░░░░░░░▌     ▐░▌     ▐░▌  ▐░▌  ▐░▌
▐░▌   ▀   ▐░▌▐░█▀▀▀▀▀▀▀█░▌     ▐░▌     ▐░▌   ▐░▌ ▐░▌
▐░▌       ▐░▌▐░▌       ▐░▌     ▐░▌     ▐░▌    ▐░▌▐░▌
▐░▌       ▐░▌▐░▌       ▐░▌ ▄▄▄▄█░█▄▄▄▄ ▐░▌     ▐░▐░▌
▐░▌       ▐░▌▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░▌      ▐░░▌
 ▀         ▀  ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀        ▀▀
*****************************************************************************/

int main() {
  // seed rand so that every run is new
  std::srand(time(NULL));

  // initializes objects
  sf::Mouse mouse;
  sf::RenderWindow window(sf::VideoMode(640, 480), "Sorting Algorithms");
  sf::Mutex algoMut;
  sf::Vector2i click;

  // create an array of random rectangles
  SV::SortRectangle *rects[NUM_RECTS];
  initRectArray(rects, window.getSize());

  // array to store the buttons in the game
  SV::Button buttons[] = {SV::Button("Quick Sort"), SV::Button("Merge Sort"),
                          SV::Button("Bubble Sort"),
                          SV::Button("Insertion Sort")};
  initButtonArray(buttons, window.getSize());

  // start theread for sorting
  sf::Thread thread(std::bind(&sortThread, rects, buttons, &mouse, &window,
                              &click, &algoMut));
  thread.launch();

  window.setFramerateLimit(60);

  // main loop
  while (window.isOpen()) {
    // reset variables
    sf::Event event;
    click.x = 0;
    click.y = 0;

    // check events
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {  // check if window is closed
        thread.terminate();
        clearRectArray(rects);
        window.close();
      } else if (event.type == sf::Event::MouseButtonPressed) {  // check mouse
        if (event.mouseButton.button == sf::Mouse::Left) {  // check left mouse
          algoMut.lock();
          click.x = event.mouseButton.x;
          click.y = event.mouseButton.y;
#ifdef DEBUG
          std::cout << "CLICK x: " << click.x << ", y: " << click.y
                    << std::endl;
#endif
          algoMut.unlock();
        }
      }
    }

    if (window.isOpen()) {  // make sure window wasn't closed
      // perform draw
      window.clear();
      for (int i = 0; i < NUM_RECTS; i++) {
        rects[i]->update();
        window.draw(*(rects[i]));
      }
      for (int i = 0; i < NUM_BUTTONS; i++) {
        if (buttons[i].active) {  // only draw buttons if active
          buttons[i].mouseUpdate(mouse.getPosition(window));  // if mouse over
          window.draw(buttons[i]);
          window.draw(*(buttons[i].getText()));
        }
      }
      window.display();
    }
  }
  return 0;
}