#include "EventHandler.h"



void EventHandler::handleEvents(WindowHandler* const windowHandler)
{   

    sf::Event event;

    while (windowHandler->_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _events.push_back(Event::CLOSE_WINDOW);
        }   
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left) //specifies
            {
                _events.push_back(Event::CLICK_MOUSE);
            }   
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                _events.push_back(Event::CLICK_ESC);
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        _events.push_back(Event::LEFT_PRESSED);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        _events.push_back(Event::RIGHT_PRESSED);
    }

}

iVector2 EventHandler::getMousePos(WindowHandler* const windowHandler)
{
    iVector2 pos = sf::Mouse::getPosition(*(windowHandler->_window));

    return pos;
}