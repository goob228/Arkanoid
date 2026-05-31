#include "WindowHandler.h"



WindowHandler::WindowHandler()
{
    _width = 500;
    _height = 500;
    createWindow();
    loadFont("C:/Windows/Fonts/ARIALI.TTF");
}

WindowHandler::WindowHandler(unsigned int const width, unsigned int const height)
{
    _width = width;
    _height = height;
    createWindow();
    loadFont("C:/Windows/Fonts/ARIALI.TTF");
}


WindowHandler::~WindowHandler()
{
    if (_window) {
        _window->close();
    }
    delete _window;
    _window = nullptr;
}

void WindowHandler::fill(Color color)
{
    _window->clear(color);
}

void WindowHandler::drawSquare(RectangleShape &shape)
{
    _window->draw(shape);
}

void WindowHandler::drawCircle(CircleShape &shape)
{
    _window->draw(shape);
}

void WindowHandler::drawText(const std::string& text, const sf::Vector2f& position,
        unsigned int characterSize, sf::Color color) {
    if (!_g_fontLoaded) return; // шрифт не загружен – ничего не рисуем

    sf::Text sfText;
    sfText.setFont(_g_font);
    sfText.setString(text);
    sfText.setCharacterSize(characterSize);
    sfText.setFillColor(color);
    sfText.setPosition(position);

    _window->draw(sfText);
}

void WindowHandler::display()
{
    _window->display();
}


void WindowHandler::render()
{
    _window->clear(GameColor::Gray);

}

void WindowHandler::createWindow()
{
    assert(_width);
    assert(_height);
    _window = new sf::RenderWindow(sf::VideoMode({_width, _height}), "Arkanoid Game", sf::Style::Close);
    assert(_window);
}

void WindowHandler::loadFont(const std::string& fontPath) {
    if (!_g_font.loadFromFile(fontPath)) {
        return;
    }
    _g_fontLoaded = true;
}
