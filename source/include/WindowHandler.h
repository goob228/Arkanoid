#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include "Base.h"
#include "SFMLtypes.h"




class WindowHandler{

    friend class EventHandler;

public:

    WindowHandler();
    WindowHandler(unsigned int const width, unsigned int const height);
    ~WindowHandler();

    void fill(Color color);
    
    void drawSquare(RectangleShape &shape);

    void drawCircle(CircleShape &shape);

    void drawText(const std::string& text, const sf::Vector2f& position,
        unsigned int characterSize = 22, sf::Color color = sf::Color::White);

    void display();

    void createWindow();

    void render();

private:

    // вызвать один раз
    void loadFont(const std::string& fontPath);

    sf::Font _g_font;
    bool _g_fontLoaded = false;

    unsigned int _width;
    unsigned int _height;

    sf::RenderWindow* _window;



};




#endif