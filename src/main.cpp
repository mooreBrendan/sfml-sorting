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
  sf::View view = window.getView();

  // create an array of random rectangles
  SV::SortRectangle *rects[NUM_RECTS] = {nullptr};

  // array to store the buttons in the game
  SV::Button buttons[] = {SV::Button("Quick Sort"), SV::Button("Merge Sort"),
                          SV::Button("Bubble Sort"),
                          SV::Button("Insertion Sort")};
  initButtonArray(buttons, window.getSize());

  // start theread for sorting
  sf::Thread thread(std::bind(&sortThread, rects, buttons, &mouse, &window,
                              &click, &algoMut));
  thread.launch();

  // set max frame rate to limit resource usage
  window.setFramerateLimit(60);

  // main loop
  while (window.isOpen()) {
    // reset variables
    sf::Event event;
    algoMut.lock();
    click.x = 0;
    click.y = 0;
    algoMut.unlock();

    // check events
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {  // check if window is closed
        thread.terminate();                   // stop the sorting thread
        clearRectArray(rects);                // free allocated data
        window.close();                       // actually close the window
      } else if (event.type == sf::Event::MouseButtonPressed) {  // check mouse
        if (event.mouseButton.button == sf::Mouse::Left) {  // check left mouse
          algoMut.lock();
          sf::Vector2f clickRaw(event.mouseButton.x, event.mouseButton.y);
          click = window.mapCoordsToPixel(clickRaw);
#ifdef DEBUG
          std::cout << "CLICK x: " << click.x << ", y: " << click.y
                    << std::endl;
#endif
          algoMut.unlock();
        }
      } else if (event.type == sf::Event::Resized) {  // check resize
        sf::Vector2f resize(event.size.width, event.size.height);

        // set minimum size
        resize.x = resize.x < MIN_X_SIZE ? MIN_X_SIZE : resize.x;
        resize.y = resize.y < MIN_Y_SIZE ? MIN_Y_SIZE : resize.y;

        // resize the window to min size and center window
        window.setSize(sf::Vector2u(resize.x, resize.y));
        view.setSize(resize);
        view.setCenter(resize.x / 2.0f, resize.y / 2.0f);
#ifdef DEBUG
        std::cout << "resize: x: " << resize.x << ", y: " << resize.y;
        std::cout << std::endl;
#endif
        window.setView(view);

        // update display objects
        algoMut.lock();
        initButtonArray(buttons, window.getSize());
        scaleRectArray(rects, window.getSize());
        algoMut.unlock();
      }
    }

    if (window.isOpen()) {  // make sure window wasn't closed
      // perform draw
      window.clear();
      algoMut.lock();
      // draw rectangles
      for (int i = 0; i < NUM_RECTS; i++) {
        if (rects[i] != nullptr) {
          rects[i]->update();
          window.draw(*(rects[i]));
        }
      }
      algoMut.unlock();

      // draw buttons
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