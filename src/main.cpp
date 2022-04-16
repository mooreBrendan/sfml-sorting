#include "main.hpp"

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